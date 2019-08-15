module type Axios_type {
  open Axios_types;
  let get: string => Js.Promise.t(response('a, 'b));
  let getc: (string, config) => Js.Promise.t(response('a, 'b));
  let postDatac: (string, Js.t('a), config) => Js.Promise.t(response('b, 'c));
  let putDatac: (string, Js.t('a), config) => Js.Promise.t(response('b, 'c));
  let deletec: (string, config) => Js.Promise.t(response('a, 'b));
}

// test variables
  let baseURL = "https://hostless.dev";
  let username = "test_username";
  let password = "test_password";

  let strContent = "string content";
  let strCID = "QmYFkqxQM63pcM5RzAQ4Fs9gei8YgHWu6DPWutfUs8Dvze";
  let jsonContent = Js.Dict.fromList([
    ("key1", "val1"),
    ("key2", "val2")
  ]);
  let jsonCID = "QmYwXpFw1QGAWxEnQWFwLuVpdbupaBcEz2DTTRRRsCt9WR";
  let testCID = "QmYp9d8BC2HhDCUVH7JEUZAd6Hbxrc5wBRfUs8TqazJJP9"
  let cidList = [|
    "QmYFkqxQM63pcM5RzAQ4Fs9gei8YgHWu6DPWutfUs8Dvze",
    "QmYwXpFw1QGAWxEnQWFwLuVpdbupaBcEz2DTTRRRsCt9WR",
    "QmYp9d8BC2HhDCUVH7JEUZAd6Hbxrc5wBRfUs8TqazJJP9"
  |];

// helpers
  let isAuthed = _cfg => [%bs.raw {|
    _cfg && _cfg.auth &&
    _cfg.auth.username === username &&
    _cfg.auth.password === password
  |}];
  
let failureResp = () => {
  Js.Promise.resolve({
    "data": [%bs.raw{|{}|}],
    "status": 500,
    "statusText": "Something went wrong",
    "config": Axios.makeConfig(),
    "headers": [%bs.raw {|{"content-type": "application/octet-stream"}|}]
  })
}

let dataResp = _data => {
  Js.Promise.resolve({
    "data": [%bs.raw {|_data|}],
    "status": 200,
    "statusText": "OK",
    "config": Axios.makeConfig(),
    "headers": [%bs.raw {|{"content-type": "application/octet-stream"}|}]
  })
}

module Axios_mock {
  let get = url => {
    let correctURL = Js.String.startsWith(baseURL ++ "/ipfs/", url)
    if(!correctURL){
      failureResp()
    }else{
      let cid = Js.String.split(baseURL ++ "/ipfs/", url)[1]
      switch (cid) {
        | "QmYFkqxQM63pcM5RzAQ4Fs9gei8YgHWu6DPWutfUs8Dvze" => dataResp(strContent)
        | "QmYwXpFw1QGAWxEnQWFwLuVpdbupaBcEz2DTTRRRsCt9WR" => dataResp(jsonContent)
        | _ => failureResp()
      }
    }
  }

  let getc = (url, cfg) => {
    let correctURL = url === (baseURL ++ "/ipfs/cids");
    if(correctURL && isAuthed(cfg)){
      dataResp(cidList)
    }else{
      failureResp()
    }
  }

  let postDatac = (url, _data, cfg) => {
    let correctURL = url === (baseURL ++ "/ipfs")
    if(correctURL && isAuthed(cfg)){
      dataResp(testCID)
    }else{
      failureResp()
    }
  }

  let putDatac = (url, _data, cfg) => {
    let correctURL = url === (baseURL ++ "/ipfs")
    if(!correctURL || !isAuthed(cfg)){
      failureResp()
    }else{
      let cid = Js.String.split(baseURL ++ "/ipfs/", url)[1];
      let validCID = Array.to_list(cidList)
      |> List.mem(cid)
      if(validCID){
        dataResp(Js.Obj.empty())
      } else{
        failureResp()
      }
    }
  }

  let deletec = (url, cfg) => {
    let correctURL = url === (baseURL ++ "/ipfs")
    if(!correctURL || !isAuthed(cfg)){
      failureResp()
    }else{
      let cid = Js.String.split(baseURL ++ "/ipfs/", url)[1];
      let validCID = Array.to_list(cidList)
      |> List.mem(cid)
      if(validCID){
        dataResp(Js.Obj.empty())
      } else{
        failureResp()
      }
    }
  }
}
