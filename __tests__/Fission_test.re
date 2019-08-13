open Jest;

[@bs.val] external baseURL: string = "process.env.INTERPLANETARY_FISSION_URL";
[@bs.val] external username: string = "process.env.INTERPLANETARY_FISSION_USERNAME";
[@bs.val] external password: string = "process.env.INTERPLANETARY_FISSION_PASSWORD";

let randomString = () => "10osidfjpaeoi4j";
let randomJSON = () => {"test": 1234}

describe("Fission.Simple", () => {
  open Expect;
  let str = randomString();
  let cid = ref("");
  let ipfsContent = ref("");

  beforeAllPromise(() => {
    Fission.addStr(baseURL, {username, password}, str)
    |> Js.Promise.then_(value => {
      cid := value;
      Fission.content(baseURL, value);
    })
    |> Js.Promise.then_(value => {
      ipfsContent := value;
      Js.Promise.resolve(value);
    })
  })

  test("same content as the original", () => {
    expect(ipfsContent^) |> toEqual(str)
  })

  test("gives properly formatted urls for IPFS content", () => {
    Fission.url(baseURL, cid^)
    |> expect
    |> toEqual(baseURL ++ "/ipfs/" ++ cid^)
  })
})

describe("Fission.User", () => {
  open Expect;
  let fission = Fission.User.create(baseURL, {username, password});

  describe("adds strings to IPFS", () => {
    let str = randomString();
    let cid = ref("");
    let cidList = ref([""]);

    beforeAllPromise(() => {
      fission.addStr(str)
      |> Js.Promise.then_(value => {
        cid := value;
        fission.cids("");
      })
      |> Js.Promise.then_(cids => {
        cidList := Array.to_list(cids);
        Js.Promise.resolve();
      })
    })

    test("uploads strings to IPFS", () => {
      let exists = List.mem(cid^, cidList^);
      expect(exists) |> toEqual(true);
    })

    testPromise("pins strings to IPFS", () => {
      fission.pin(cid^)
      |> Js.Promise.then_(_value => {
        expect(true)
        |> toEqual(true)
        |> Js.Promise.resolve
      })
    })

    describe("string retrieval", () => {
      let ipfsContent = ref("");

      beforeAllPromise(() => {
        fission.content(cid^)
        |> Js.Promise.then_(value => {
          ipfsContent := value
          Js.Promise.resolve()
        })
      })

      test("is the same string as the original", () => {
        expect(ipfsContent^) |> toEqual(str);
      })

    })

    testPromise("removes strings from IPFS", () => {
      fission.remove(cid^)
      |> Js.Promise.then_(_value => {
        fission.cids("");
      })
      |> Js.Promise.then_(cids => {
        Array.to_list(cids)
        |> List.mem(cid^)
        |> expect
        |> toEqual(false)
        |> Js.Promise.resolve
      })
    })
  })

  describe("adds JSON Objects to IPFS", () => {
    let json = randomJSON();
    let cid = ref("");
    let cidList = ref([""]);

    beforeAllPromise(() => {
      fission.add(json)
      |> Js.Promise.then_(value => {
        cid := value;
        fission.cids("");
      })
      |> Js.Promise.then_(cids => {
        cidList := Array.to_list(cids)
        Js.Promise.resolve();
      })
    })

    test("uploads json to IPFS", () => {
      let exists = List.mem(cid^, cidList^)
      expect(exists) |> toEqual(true)
    })

    testPromise("pins json to IPFS", () => {
      fission.pin(cid^)
      |> Js.Promise.then_(_value => {
        expect(true)
        |> toEqual(true)
        |> Js.Promise.resolve
      })
    })

    describe("string retrieval", () => {
      let ipfsContent = ref({"test": 0})

      beforeAllPromise(() => {
        fission.content(cid^)
        |> Js.Promise.then_(value => {
          ipfsContent := value
          Js.Promise.resolve()
        })
      })

      test("is the same string as the original", () => {
        expect(ipfsContent^) |> toEqual(json)
      })

    })

    testPromise("removes json from IPFS", () => {
      fission.remove(cid^)
      |> Js.Promise.then_(_value => {
        fission.cids("")
      })
      |> Js.Promise.then_(cids => {
        Array.to_list(cids)
        |> List.mem(cid^)
        |> expect
        |> toEqual(false)
        |> Js.Promise.resolve
      })
    })
  })

})