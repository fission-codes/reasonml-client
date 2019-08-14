// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var Fs = require("fs");
var Jest = require("@glennsl/bs-jest/src/jest.js");
var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Mocks$ReasonmlClient = require("../src/Mocks.bs.js");
var Fission$ReasonmlClient = require("../src/Fission.bs.js");

function randomString(param) {
  return "10osidfjpaeoi4j";
}

function randomJSON(param) {
  return Js_dict.fromList(/* :: */[
              /* tuple */[
                "10osidfjpaeoi4j",
                "10osidfjpaeoi4j"
              ],
              /* [] */0
            ]);
}

var FissionMock = Fission$ReasonmlClient.FissionInject(Mocks$ReasonmlClient.AxiosMock);

Jest.describe("Fission.Simple", (function (param) {
        var str = "10osidfjpaeoi4j";
        var cid = /* record */[/* contents */""];
        var ipfsContent = /* record */[/* contents */""];
        Jest.beforeAllPromise(undefined, (function (param) {
                return Fission$ReasonmlClient.addString(process.env.INTERPLANETARY_FISSION_URL, /* record */[
                                /* username */process.env.INTERPLANETARY_FISSION_USERNAME,
                                /* password */process.env.INTERPLANETARY_FISSION_PASSWORD
                              ], str).then((function (value) {
                                cid[0] = value;
                                return Fission$ReasonmlClient.content(process.env.INTERPLANETARY_FISSION_URL, value);
                              })).then((function (value) {
                              ipfsContent[0] = value;
                              return Promise.resolve(value);
                            }));
              }));
        Jest.test("same content as the original", (function (param) {
                return Jest.Expect[/* toEqual */12](str, Jest.Expect[/* expect */0](ipfsContent[0]));
              }));
        return Jest.test("gives properly formatted urls for IPFS content", (function (param) {
                      return Jest.Expect[/* toEqual */12](process.env.INTERPLANETARY_FISSION_URL + ("/ipfs/" + cid[0]), Jest.Expect[/* expect */0](Fission$ReasonmlClient.url(process.env.INTERPLANETARY_FISSION_URL, cid[0])));
                    }));
      }));

Jest.describe("Fission.User", (function (param) {
        var fission = Fission$ReasonmlClient.User[/* create */0](process.env.INTERPLANETARY_FISSION_URL, /* record */[
              /* username */process.env.INTERPLANETARY_FISSION_USERNAME,
              /* password */process.env.INTERPLANETARY_FISSION_PASSWORD
            ]);
        Jest.describe("adds strings to IPFS", (function (param) {
                var str = "10osidfjpaeoi4j";
                var cid = /* record */[/* contents */""];
                var cidList = /* record */[/* contents : :: */[
                    "",
                    /* [] */0
                  ]];
                Jest.beforeAllPromise(undefined, (function (param) {
                        return Curry._1(fission[/* addString */5], str).then((function (value) {
                                        cid[0] = value;
                                        return Curry._1(fission[/* cids */3], /* () */0);
                                      })).then((function (cids) {
                                      cidList[0] = $$Array.to_list(cids);
                                      return Promise.resolve(/* () */0);
                                    }));
                      }));
                Jest.test("uploads strings to IPFS", (function (param) {
                        var exists = List.mem(cid[0], cidList[0]);
                        return Jest.Expect[/* toEqual */12](true, Jest.Expect[/* expect */0](exists));
                      }));
                Jest.testPromise("pins strings to IPFS", undefined, (function (param) {
                        return Curry._1(fission[/* pin */7], cid[0]).then((function (_value) {
                                      return Promise.resolve(Jest.Expect[/* toEqual */12](true, Jest.Expect[/* expect */0](true)));
                                    }));
                      }));
                Jest.describe("string retrieval", (function (param) {
                        var ipfsContent = /* record */[/* contents */""];
                        Jest.beforeAllPromise(undefined, (function (param) {
                                return Curry._1(fission[/* content */2], cid[0]).then((function (value) {
                                              ipfsContent[0] = value;
                                              return Promise.resolve(/* () */0);
                                            }));
                              }));
                        return Jest.test("is the same string as the original", (function (param) {
                                      return Jest.Expect[/* toEqual */12](str, Jest.Expect[/* expect */0](ipfsContent[0]));
                                    }));
                      }));
                return Jest.testPromise("removes strings from IPFS", undefined, (function (param) {
                              return Curry._1(fission[/* remove */8], cid[0]).then((function (_value) {
                                              return Curry._1(fission[/* cids */3], /* () */0);
                                            })).then((function (cids) {
                                            return Promise.resolve(Jest.Expect[/* toEqual */12](false, Jest.Expect[/* expect */0](List.mem(cid[0], $$Array.to_list(cids)))));
                                          }));
                            }));
              }));
        Jest.describe("adds JSON Objects to IPFS", (function (param) {
                var json = randomJSON(/* () */0);
                var cid = /* record */[/* contents */""];
                var cidList = /* record */[/* contents : :: */[
                    "",
                    /* [] */0
                  ]];
                Jest.beforeAllPromise(undefined, (function (param) {
                        return Curry._1(fission[/* add */4], json).then((function (value) {
                                        cid[0] = value;
                                        return Curry._1(fission[/* cids */3], /* () */0);
                                      })).then((function (cids) {
                                      cidList[0] = $$Array.to_list(cids);
                                      return Promise.resolve(/* () */0);
                                    }));
                      }));
                Jest.test("uploads json to IPFS", (function (param) {
                        var exists = List.mem(cid[0], cidList[0]);
                        return Jest.Expect[/* toEqual */12](true, Jest.Expect[/* expect */0](exists));
                      }));
                Jest.testPromise("pins json to IPFS", undefined, (function (param) {
                        return Curry._1(fission[/* pin */7], cid[0]).then((function (_value) {
                                      return Promise.resolve(Jest.Expect[/* toEqual */12](true, Jest.Expect[/* expect */0](true)));
                                    }));
                      }));
                Jest.describe("string retrieval", (function (param) {
                        var ipfsContent = /* record */[/* contents */{ }];
                        Jest.beforeAllPromise(undefined, (function (param) {
                                return Curry._1(fission[/* content */2], cid[0]).then((function (value) {
                                              ipfsContent[0] = value;
                                              return Promise.resolve(/* () */0);
                                            }));
                              }));
                        return Jest.test("is the same string as the original", (function (param) {
                                      return Jest.Expect[/* toEqual */12](json, Jest.Expect[/* expect */0](ipfsContent[0]));
                                    }));
                      }));
                return Jest.testPromise("removes json from IPFS", undefined, (function (param) {
                              return Curry._1(fission[/* remove */8], cid[0]).then((function (_value) {
                                              return Curry._1(fission[/* cids */3], /* () */0);
                                            })).then((function (cids) {
                                            return Promise.resolve(Jest.Expect[/* toEqual */12](false, Jest.Expect[/* expect */0](List.mem(cid[0], $$Array.to_list(cids)))));
                                          }));
                            }));
              }));
        return Jest.describe("adds files to IPFS", (function (param) {
                      var filepath = __dirname + "/test_img.png";
                      var fileContent = Fs.readFileSync(filepath, "utf8");
                      var cid = /* record */[/* contents */""];
                      var cidList = /* record */[/* contents : :: */[
                          "",
                          /* [] */0
                        ]];
                      Jest.beforeAllPromise(undefined, (function (param) {
                              var fileStream = (
        require('fs').createReadStream(filepath)
      );
                              return Curry._1(fission[/* addStream */6], fileStream).then((function (value) {
                                              cid[0] = value;
                                              return Curry._1(fission[/* cids */3], /* () */0);
                                            })).then((function (cids) {
                                            cidList[0] = $$Array.to_list(cids);
                                            return Promise.resolve(/* () */0);
                                          }));
                            }));
                      Jest.test("uploads files to IPFS", (function (param) {
                              var exists = List.mem(cid[0], cidList[0]);
                              return Jest.Expect[/* toEqual */12](true, Jest.Expect[/* expect */0](exists));
                            }));
                      Jest.testPromise("pins files to IPFS", undefined, (function (param) {
                              return Curry._1(fission[/* pin */7], cid[0]).then((function (_value) {
                                            return Promise.resolve(Jest.Expect[/* toEqual */12](true, Jest.Expect[/* expect */0](true)));
                                          }));
                            }));
                      Jest.describe("file retrieval", (function (param) {
                              var ipfsContent = /* record */[/* contents */""];
                              Jest.beforeAllPromise(undefined, (function (param) {
                                      return Curry._1(fission[/* content */2], cid[0]).then((function (value) {
                                                    ipfsContent[0] = value;
                                                    return Promise.resolve(/* () */0);
                                                  }));
                                    }));
                              return Jest.test("is the same file as the original", (function (param) {
                                            return Jest.Expect[/* toEqual */12](fileContent, Jest.Expect[/* expect */0](ipfsContent[0]));
                                          }));
                            }));
                      return Jest.testPromise("removes files from IPFS", undefined, (function (param) {
                                    return Curry._1(fission[/* remove */8], cid[0]).then((function (_value) {
                                                    return Curry._1(fission[/* cids */3], /* () */0);
                                                  })).then((function (cids) {
                                                  return Promise.resolve(Jest.Expect[/* toEqual */12](false, Jest.Expect[/* expect */0](List.mem(cid[0], $$Array.to_list(cids)))));
                                                }));
                                  }));
                    }));
      }));

exports.randomString = randomString;
exports.randomJSON = randomJSON;
exports.FissionMock = FissionMock;
/* FissionMock Not a pure module */
