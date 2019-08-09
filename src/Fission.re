  ///////////
 // Types //
///////////

type cid = string;

type auth = {
  username: string,
  password: string,
};

type fsnUser('a) = {
  add:     Js.t('a) => Js.Promise.t(Js.Promise.error),
  addStr:  cid      => Js.Promise.t(Js.Promise.error),
  base:    string,
  content: cid      => Js.Promise.t(Js.Promise.error),
  pin:     cid      => Js.Promise.t(Js.Promise.error),
  remove:  cid      => Js.Promise.t(Js.Promise.error),
  url:     cid      => string
};

type fsn('a) = {
  base:    string,
  content: cid => Js.Promise.t(Js.Promise.error),
  login:   (string, string) => fsnUser('a),
  url:     cid => string
};

  ///////////////
 // Constants //
///////////////

let baseURL = "http://localhost:1337";
let ipfsURL = baseURL ++ "/ipfs";
let cidsURL = ipfsURL ++ "/cids"

let env_username = "ca2c70bc13298c5109ee";
let env_password = "VlBgonAFjZon2wd2VkTR3uc*p-XMd(L_Zf$nFvACpHQShqJ_Hp2Pa";

  ///////////////
 // Functions //
///////////////

// Helpers

let url = (domain: string, cid: cid) => domain ++ "/ipfs/" ++ cid;

let convAuth = (auth: auth) => {
  "username": auth.username,
  "password": auth.password,
};

let handle = a =>
  a
|> Js.Promise.then_(response => Js.Promise.resolve(response##data))
|> Js.Promise.catch(Js.Promise.resolve);


let octetHeader = Axios.Headers.fromObj({"content-type": "application/octet-stream"});
let octetConfig = auth => Axios.makeConfig(~auth=convAuth(auth), ~headers=octetHeader, ());
let blankConfig = auth => Axios.makeConfig(~auth=convAuth(auth), ());

// Main Show

let content = (cid: cid) =>
  baseURL
  -> url(cid)
  -> Axios.get
  -> handle

let list = (auth: auth) =>
  cidsURL
  -> Axios.getc(blankConfig(auth))
  -> handle

let add = (auth: auth, content: 'a) =>
  ipfsURL
  -> Axios.postDatac(content, octetConfig(auth))
  -> handle

let addStr = (auth: auth, _str: string) =>
  ipfsURL
  -> Axios.postDatac([%bs.raw {|str|}], octetConfig(auth))
  -> handle

let pin = (auth: auth, cid: cid) =>
  baseURL
  -> url(cid)
  -> Axios.putDatac([%bs.raw {|{}|}], blankConfig(auth))
  -> handle

let remove = (auth: auth, cid: cid) =>
  baseURL
  -> url(cid)
  -> Axios.deletec(blankConfig(auth))
  -> handle

  /////////////
 // Records //
/////////////

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
  {
    base,
    content,
    login: fissionUser(base),
    url:   url(base)
  };
};

let instance: fsn(string) = fission(baseURL);
