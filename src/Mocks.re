module type AxiosType {
  open Axios_types;
  let get: string => Js.Promise.t(response('a, 'b));
  let getc: (string, config) => Js.Promise.t(response('a, 'b));
  let postDatac: (string, Js.t('a), config) => Js.Promise.t(response('b, 'c));
  let putDatac: (string, Js.t('a), config) => Js.Promise.t(response('b, 'c));
  let deletec: (string, config) => Js.Promise.t(response('a, 'b));
}


// test variables
let baseURL = "https://hostless.dev"
let username = "test_username"
let password = "test_password"

let strContent = "string content"
// const jsonContent = {
//   string: 'testing',
//   array: [1, -1, 1000, 0]
// } as JSONObject
let testCID = "QmYFkqxQM63pcM5RzAQ4Fs9gei8YgHWu6DPWutfUs8Dvze"
let testCIDs = [|
  "QmYFkqxQM63pcM5RzAQ4Fs9gei8YgHWu6DPWutfUs8Dvze",
  "QmYp9d8BC2HhDCUVH7JEUZAd6Hbxrc5wBRfUs8TqazJJP9",
  "QmYwXpFw1QGAWxEnQWFwLuVpdbupaBcEz2DTTRRRsCt9WR"
|]

module AxiosMock {
  // open Axios_types;

  let get = Axios.get
  // let get = _cid => {
  //   let response = {
  //     "data": strContent,
  //     "status": 200,
  //     "statusText": "OK",
  //     "config": Axios.makeConfig(),
  //     "headers": Axios.Headers.fromObj({"content-type": "application/octet-stream"})
  //   }
  //   Js.Promise.resolve(response)
  // }

  let getc = Axios.getc

  let postDatac = Axios.postDatac
  // let postDatac = (_url: string, _data: Js.t('a), _config: Axios_types.config) => {
  //   let response: Axios_types.response('a, 'b) = {
  //     "data": testCID,
  //     "status": 200,
  //     "statusText": "OK",
  //     "headers": Axios.Headers.fromObj({{"content-type": "text/plain; charset=utf-8"}}),
  //     "config": Axios.makeConfig()
  //   }
  //   Js.Promise.resolve(response)
  // }

  let putDatac = Axios.putDatac
  let deletec = Axios.deletec

}
