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

let add = (content: 'a, auth: auth) =>
  Js.Promise.(
    Axios.postDatac(
      baseURL ++ "/ipfs/",
      content,
      Axios.makeConfig(~auth=convAuth(auth), ~headers=octetHeader, ()),
    )
    |> then_(response => resolve(response##data))
    |> catch(error => resolve(error))
  );

let addStr = (_str: string, auth: auth) =>
  Js.Promise.(
    Axios.postDatac(
      baseURL ++ "/ipfs/",
      [%bs.raw {|str|}],
      Axios.makeConfig(~auth=convAuth(auth), ~headers=octetHeader, ()),
    )
    |> then_(response => resolve(response##data))
    |> catch(error => resolve(error))
  );

let pin = (cid: cid, auth: auth) =>
  Js.Promise.(
    Axios.putDatac(
      url(baseURL, cid),
      [%bs.raw {|{}|}],
      Axios.makeConfig(~auth=convAuth(auth), ()),
    )
    |> then_(response => resolve(response##data))
    |> catch(error => resolve(error))
  );

let remove = (cid: cid, auth: auth) =>
  Js.Promise.(
    Axios.deletec(
      url(baseURL, cid),
      Axios.makeConfig(~auth=convAuth(auth), ()),
    )
    |> then_(response => resolve(response##data))
    |> catch(error => resolve(error))
  );

// testing purposes, delete later
let user = {username: env_username, password: env_password};
Js.Promise.(
  remove("QmQbPPkak9itW3v8WSohtonCBiJcrnAUhrSW1TGPnmWe3f", user)
  |> then_(result => resolve(Js.Console.log(result)))
  |> catch(error => resolve(Js.Console.log(error)))
);