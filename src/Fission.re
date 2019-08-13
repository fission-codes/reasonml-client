// Types

[@gentype]
type cid = string;
[@gentype]

type auth = {
  username: string,
  password: string,
};

// Helpers

let await = promise =>
  promise
  |> Js.Promise.then_(response => Js.Promise.resolve(response##data))
  // |> Js.Promise.catch(err => Js.Promise.resolve(""));

let convAuth = auth => { "username": auth.username, "password": auth.password, };
let octetHeader = Axios.Headers.fromObj({"content-type": "application/octet-stream"});
let octetConfig = auth => Axios.makeConfig(~auth=convAuth(auth), ~headers=octetHeader, ());
let blankConfig = auth => Axios.makeConfig(~auth=convAuth(auth), ());

[@gentype]
let ipfsURL = (domain) => domain ++ "/ipfs";
[@gentype]
let cidsURL = (domain) => ipfsURL(domain) ++ "/cids";
[@gentype]
let url = (domain, cid) => ipfsURL(domain) ++ "/" ++ cid;

// Main Show

[@gentype]
let content = (base, cid) =>
  url(base, cid)
  -> Axios.get
  -> await;

[@gentype]
let cids = (base, auth, _str) =>
  cidsURL(base)
  -> Axios.getc(blankConfig(auth))
  -> await;

[@gentype]
let add = (base, auth, content) =>
  ipfsURL(base)
  -> Axios.postDatac(content, octetConfig(auth))
  -> await;

[@gentype]
let addStr = (base, auth, _str) => {
  ipfsURL(base)
  -> Axios.postDatac([%bs.raw {|_str|}], octetConfig(auth))
  -> await;
};

[@gentype]
let pin = (base, auth, cid) =>
  url(base, cid)
  -> Axios.putDatac(Js.Obj.empty(), blankConfig(auth))
  -> await;

[@gentype]
let remove = (base, auth, cid) =>
  url(base, cid)
  -> Axios.deletec(blankConfig(auth))
  -> await;

// Modules

module Simple {
  type t = {
    base:    string,
    url:     cid => string,
    content: cid => Js.Promise.t(string)
  };

  [@gentype]
  let create = base => {
    base,
    url: url(base),
    content: content(base)
  }
}
[@gentype]
let newSimple = Simple.create;

module User {
  type t('content) = {
    base:    string,
    url:     cid => string,
    content: cid => Js.Promise.t(string),
    cids:    string => Js.Promise.t(list(string)),
    add:     Js.t('content) => Js.Promise.t(string),
    addStr:  cid => Js.Promise.t(string),
    pin:     cid => Js.Promise.t(string),
    remove:  cid => Js.Promise.t(string),
  };

  let create = (base, auth) => {
    base,
    url: url(base),
    content: content(base),
    cids: cids(base, auth),
    add: add(base, auth),
    addStr: addStr(base, auth),
    pin: pin(base, auth),
    remove: remove(base, auth),
  }
}
[@gentype]
let newUser = User.create