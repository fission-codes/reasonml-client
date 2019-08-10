// Types

type cid = string;

type auth = {
  username: string,
  password: string,
};

type fsnUser('content) = {
  base:    string,
  add:     Js.t('content) => Js.Promise.t(Js.Promise.error),
  addStr:  cid => Js.Promise.t(Js.Promise.error),
  content: cid => Js.Promise.t(Js.Promise.error),
  pin:     cid => Js.Promise.t(Js.Promise.error),
  remove:  cid => Js.Promise.t(Js.Promise.error),
  url:     cid => string
};

type fsn('content) = {
  base:    string,
  login:   (string, string) => fsnUser('content),
  content: cid => Js.Promise.t(Js.Promise.error),
  url:     cid => string
};

// Constants

let baseURL = "http://localhost:1337";
let ipfsURL = baseURL ++ "/ipfs";
let cidsURL = ipfsURL ++ "/cids"

let env_username = "ca2c70bc13298c5109ee";
let env_password = "VlBgonAFjZon2wd2VkTR3uc*p-XMd(L_Zf$nFvACpHQShqJ_Hp2Pa";

// Helpers

let convAuth = auth => {
  "username": auth.username,
  "password": auth.password,
};

let await = promise =>
  promise
  |> Js.Promise.then_(response => Js.Promise.resolve(response##data))
  |> Js.Promise.catch(Js.Promise.resolve);

let url = (domain: string, cid: cid) => domain ++ "/ipfs/" ++ cid;
let octetHeader = Axios.Headers.fromObj({"content-type": "application/octet-stream"});
let octetConfig = auth => Axios.makeConfig(~auth=convAuth(auth), ~headers=octetHeader, ());
let blankConfig = auth => Axios.makeConfig(~auth=convAuth(auth), ());

// Main Show

let content = cid =>
  baseURL
  -> url(cid)
  -> Axios.get
  -> await

let list = auth =>
  cidsURL
  -> Axios.getc(blankConfig(auth))
  -> await

let add = (auth, content) =>
  ipfsURL
  -> Axios.postDatac(content, octetConfig(auth))
  -> await

let addStr = (auth, _str) =>
  ipfsURL
  -> Axios.postDatac([%bs.raw {|str|}], octetConfig(auth))
  -> await

let pin = (auth, cid) =>
  baseURL
  -> url(cid)
  -> Axios.putDatac(Js.Obj.empty(), blankConfig(auth))
  -> await

let remove = (auth, cid) =>
  baseURL
  -> url(cid)
  -> Axios.deletec(blankConfig(auth))
  -> await

// Records

let fissionUser = (base, username, password) => {
  let user = {username, password};

  {
    base,
    content,
    add:    add(user),
    addStr: addStr(user),
    pin:    pin(user),
    remove: remove(user),
    url:    url(base)
  };
};

let fission = base => {
  base,
  content,
  login: fissionUser(base),
  url:   url(base)
};

let instance: fsn(string) = fission(baseURL);
