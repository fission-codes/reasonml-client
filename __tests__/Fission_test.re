open Jest;

[@bs.val] external baseURL: string = "process.env.INTERPLANETARY_FISSION_URL";
[@bs.val] external username: string = "process.env.INTERPLANETARY_FISSION_USERNAME";
[@bs.val] external password: string = "process.env.INTERPLANETARY_FISSION_PASSWORD";

let randomString() = "10osidfjpaeoi4j"

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
    expect(Fission.url(baseURL, cid^)) |> toEqual(baseURL ++ "/ipfs/" ++ cid^)
  })
})

describe("Fission.User", () => {
  open Expect;
  let fission = Fission.User.create(baseURL, {username, password})

  describe("adds strings to IPFS", () => {
    let str = randomString();
    let cid = ref("")
    let cidList = ref([""])

    beforeAllPromise(() => {
      fission.addStr(str)
      |> Js.Promise.then_(value => {
        cid := value;
        fission.cids("");
      })
      |> Js.Promise.then_(cids => {
        cidList := Array.to_list(cids)
        Js.Promise.resolve(cids);
      })
    })

    test("uploads strings to IPFS", () => {
      let exists = List.mem(cid^, cidList^)
      expect(exists) |> toEqual(true)
    })

    testPromise("pins strings to IPFS", () => {
      fission.pin(cid^)
      |> Js.Promise.then_(_value => {
        Js.Promise.resolve(expect(true) |> toEqual(true))
      })
    })

    describe("string retrieval", () => {
      let ipfsContent = ref("")

      beforeAllPromise(() => {
        fission.content(cid^)
        |> Js.Promise.then_(value => {
          ipfsContent := value
          Js.Promise.resolve()
        })
      })

      test("is the same string as the original", () => {
        expect(ipfsContent^) |> toEqual(str)
      })

    })

    testPromise("removes strings from IPFS", () => {
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