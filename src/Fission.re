type cid = string;

let await = promise =>
  promise
  |> Js.Promise.then_(response => Js.Promise.resolve(response##data))
  |> Js.Promise.catch(Js.Promise.resolve);

let octetHeader = Axios.Headers.fromObj({"content-type": "application/octet-stream"});

module type URL = {
  let baseUrl: string;
};

module type Auth = {
  let username: string;
  let password: string;
};

module Simple = (Base: URL) => {
  let ipfsURL = Base.baseUrl ++ "/ipfs";
  let cidsURL = ipfsURL ++ "/cids"
  let url     = cid => ipfsURL ++ cid;

  let content = cid =>
    cid
    -> url
    -> Axios.get
    -> await;
};

module User = (Base: URL, Auth: Auth) => {
  include Simple(Base);

  let auth = {
    "username": Auth.username,
    "password": Auth.password,
  };

  let octetConfig = Axios.makeConfig(~auth, ~headers=octetHeader, ());
  let blankConfig = Axios.makeConfig(~auth, ());

  let myCIDs = () =>
    cidsURL
    -> Axios.getc(blankConfig)
    -> await;

  let add = content =>
    ipfsURL
    -> Axios.postDatac(content, octetConfig)
    -> await;

  let addStr = _str =>
    ipfsURL
    -> Axios.postDatac([%bs.raw {|str|}], octetConfig)
    -> await;

  let pin = cid =>
    cid
    -> url
    -> Axios.putDatac(Js.Obj.empty(), blankConfig)
    -> await;

  let remove = cid =>
    cid
    -> url
    -> Axios.deletec(blankConfig)
    -> await;
};

////////////////////////////////////////////////////////////////////////////////

module DefaultURL = {
  let baseUrl = "http://localhost:1337";
};

module DefaultAuth = {
  let username = "ca2c70bc13298c5109ee";
  let password = "VlBgonAFjZon2wd2VkTR3uc*p-XMd(L_Zf$nFvACpHQShqJ_Hp2Pa";
};

module Foo = Simple(DefaultURL);
module Bar = User(DefaultURL, DefaultAuth);

let server = Foo.ipfsURL;
let myCIDs = Bar.myCIDs
