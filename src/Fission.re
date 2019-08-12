// Types

type cid = string;

type auth = {
  username: string,
  password: string,
};

// Helpers

let await = promise =>
  promise
  |> Js.Promise.then_(response => Js.Promise.resolve(response##data))
  |> Js.Promise.catch(Js.Promise.resolve);

let convAuth = auth => { "username": auth.username, "password": auth.password, };
let octetHeader = Axios.Headers.fromObj({"content-type": "application/octet-stream"});
let octetConfig = auth => Axios.makeConfig(~auth=convAuth(auth), ~headers=octetHeader, ());
let blankConfig = auth => Axios.makeConfig(~auth=convAuth(auth), ());

let ipfsURL = (domain) => domain ++ "/ipfs";
let cidsURL = (domain) => ipfsURL(domain) ++ "/cids"
let url = (domain, cid) => ipfsURL(domain) ++ "/" ++ cid;

// Main Show

let content = (base, cid) =>
  url(base, cid)
  -> Axios.get
  -> await

let list = (base, auth) =>
  cidsURL(base)
  -> Axios.getc(blankConfig(auth))
  -> await

let add = (base, auth, content) =>
  ipfsURL(base)
  -> Axios.postDatac(content, octetConfig(auth))
  -> await

let addStr = (base, auth, _str) =>
  ipfsURL(base)
  -> Axios.postDatac([%bs.raw {|str|}], octetConfig(auth))
  -> await

let pin = (base, auth, cid) =>
  url(base, cid)
  -> Axios.putDatac(Js.Obj.empty(), blankConfig(auth))
  -> await

let remove = (base, auth, cid) =>
  url(base, cid)
  -> Axios.deletec(blankConfig(auth))
  -> await

// Records

module Simple {
  type t = {
    base:    string,
    url:     cid => string,
    content: cid => Js.Promise.t(Js.Promise.error)
  };

  let create = base => {
    base,
    url: url(base),
    content: content(base)
  }
}

module User {
  type t('content) = {
    base:    string,
    url:     cid => string,
    content: cid => Js.Promise.t(Js.Promise.error),
    add:     Js.t('content) => Js.Promise.t(Js.Promise.error),
    addStr:  cid => Js.Promise.t(Js.Promise.error),
    pin:     cid => Js.Promise.t(Js.Promise.error),
    remove:  cid => Js.Promise.t(Js.Promise.error),
  };

  let create = (base, auth) => {
    base,
    url: url(base),
    content: content(base),
    add: add(base, auth),
    addStr: addStr(base, auth),
    pin: pin(base, auth),
    remove: remove(base, auth),
  }
}
