module FissionInject = (Axios_impl: Mocks.Axios_type) => {
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
    -> Axios_impl.get
    -> await;

  [@gentype]
  let cids = (base, auth, ()) =>
    cidsURL(base)
    -> Axios_impl.getc(blankConfig(auth))
    -> await;

  [@gentype]
  let add = (base, auth, _content) =>
    ipfsURL(base)
    -> Axios_impl.postDatac([%bs.raw {|_content|}], octetConfig(auth))
    -> await;

  [@gentype]
  let addString = (base, auth, _str: string) => {
    ipfsURL(base)
    -> Axios_impl.postDatac([%bs.raw {|_str|}], octetConfig(auth))
    -> await;
  };

  [@gentype]
  let addStream = (base, auth, _stream: Stream.t(char)) => {
    ipfsURL(base)
    -> Axios_impl.postDatac([%bs.raw {|_stream|}], octetConfig(auth))
    -> await;
  };

  [@gentype]
  let pin = (base, auth, cid) =>
    url(base, cid)
    -> Axios_impl.putDatac(Js.Obj.empty(), blankConfig(auth))
    -> await;

  [@gentype]
  let remove = (base, auth, cid) =>
    url(base, cid)
    -> Axios_impl.deletec(blankConfig(auth))
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
    type t('ipfs, 'content) = {
      base:    string,
      url:     cid => string,
      content: cid => Js.Promise.t('ipfs),
      cids:    unit => Js.Promise.t(array(string)),
      // add:     Js.t('content) => Js.Promise.t(string),
      add:     Js.Dict.t(string) => Js.Promise.t(string),
      addString:  cid => Js.Promise.t(string),
      addStream:  Stream.t(char) => Js.Promise.t(string),
      pin:     cid => Js.Promise.t(string),
      remove:  cid => Js.Promise.t(string),
    };

    let create = (base, auth) => {
      base,
      url: url(base),
      content: content(base),
      cids: cids(base, auth),
      add: add(base, auth),
      addString: addString(base, auth),
      addStream: addStream(base, auth),
      pin: pin(base, auth),
      remove: remove(base, auth),
    }
  }
  [@gentype]
  let newUser = User.create
}

include FissionInject(Axios);