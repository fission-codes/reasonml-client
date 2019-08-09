let baseURL = "http://localhost:1337";
let env_username = "ca2c70bc13298c5109ee";
let env_password = "VlBgonAFjZon2wd2VkTR3uc*p-XMd(L_Zf$nFvACpHQShqJ_Hp2Pa";

type cid = string;
type auth = {
  username: string,
  password: string,
};

let octetHeader =
  Axios.Headers.fromObj({"content-type": "application/octet-stream"});

let convAuth = (auth: auth) => {
  "username": auth.username,
  "password": auth.password,
};

let url = (baseURL: string, cid: cid) => baseURL ++ "/ipfs/" ++ cid;

let content = (cid: cid) =>
  Js.Promise.(
    Axios.get(url(baseURL, cid))
    |> then_(response => resolve(response##data))
    |> catch(error => resolve(error))
  );

let list = (auth: auth) =>
  Js.Promise.(
    Axios.getc(
      baseURL ++ "/ipfs/cids",
      Axios.makeConfig(~auth=convAuth(auth), ()),
    )
    |> then_(response => resolve(response##data))
    |> catch(error => resolve(error))
  );

let add = (auth: auth, content: 'a) =>
  Js.Promise.(
    Axios.postDatac(
      baseURL ++ "/ipfs/",
      content,
      Axios.makeConfig(~auth=convAuth(auth), ~headers=octetHeader, ()),
    )
    |> then_(response => resolve(response##data))
    |> catch(error => resolve(error))
  );

let addStr = (auth: auth, _str: string) =>
  Js.Promise.(
    Axios.postDatac(
      baseURL ++ "/ipfs/",
      [%bs.raw {|str|}],
      Axios.makeConfig(~auth=convAuth(auth), ~headers=octetHeader, ()),
    )
    |> then_(response => resolve(response##data))
    |> catch(error => resolve(error))
  );

let pin = (auth: auth, cid: cid) =>
  Js.Promise.(
    Axios.putDatac(
      url(baseURL, cid),
      [%bs.raw {|{}|}],
      Axios.makeConfig(~auth=convAuth(auth), ()),
    )
    |> then_(response => resolve(response##data))
    |> catch(error => resolve(error))
  );

let remove = (auth: auth, cid: cid) =>
  Js.Promise.(
    Axios.deletec(
      url(baseURL, cid),
      Axios.makeConfig(~auth=convAuth(auth), ()),
    )
    |> then_(response => resolve(response##data))
    |> catch(error => resolve(error))
  );

type fsnUser('a) = {
  base: string,
  content: cid => Js.Promise.t(Js.Promise.error),
  url: cid => string,
  add: Js.t('a) => Js.Promise.t(Js.Promise.error),
  addStr: cid => Js.Promise.t(Js.Promise.error),
  pin: cid => Js.Promise.t(Js.Promise.error),
  remove: cid => Js.Promise.t(Js.Promise.error),
};

type fsn('a) = {
  base: string,
  content: cid => Js.Promise.t(Js.Promise.error),
  url: cid => string,
  login: (string, string) => fsnUser('a),
};

let fissionUser =
    (base: string, username: string, password: string): fsnUser('a) => {
  let user = {username, password};
  {
    base,
    content,
    url: url(base),
    add: add(user),
    addStr: addStr(user),
    pin: pin(user),
    remove: remove(user),
  };
};

let fission = (base: string): fsn('a) => {
  {base, content, url: url(base), login: fissionUser(base)};
};

let instance = fission(baseURL);