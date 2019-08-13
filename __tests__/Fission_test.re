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
  // let fission = Fission.User.create(baseURL, {username, password})

  describe("adds strings to IPFS", () => {
    let str = randomString();
    let cid = ref("")
    let ipfsContent = ref("")

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

    test("filler", () => {
      expect("1234") |> toEqual("1234")
    })
  })
})