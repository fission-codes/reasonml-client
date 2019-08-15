open Jest;

module FissionMock = Fission.FissionInject(Mocks.Axios_mock);

describe("Fission.Simple", () => {
  open Expect;

  test("gives properly formatted urls for IPFS content", () => {
    Fission.url(Mocks.baseURL, Mocks.strCID)
    |> expect
    |> toEqual(Mocks.baseURL ++ "/ipfs/" ++ Mocks.strCID)
  })

  describe("retrieves string content", () => {
    let ipfsContent = ref("");
    beforeAllPromise(() => {
      FissionMock.content(Mocks.baseURL, Mocks.strCID)
      |> Js.Promise.then_(value => {
        ipfsContent := value;
        Js.Promise.resolve(value);
      })
    })

    test("same content as the original", () => {
      expect(ipfsContent^) |> toEqual(Mocks.strContent)
    })
  })

  describe("retrieves json content", () => {
    let ipfsContent = ref(Js.Dict.empty());
    beforeAllPromise(() => {
      FissionMock.content(Mocks.baseURL, Mocks.jsonCID)
      |> Js.Promise.then_(value => {
        ipfsContent := value;
        Js.Promise.resolve(value);
      })
    })

    test("same content as the original", () => {
      expect(ipfsContent^) |> toEqual(Mocks.jsonContent)
    })
  })
})

describe("Fission.User", () => {
  open Expect;
  let fission = FissionMock.User.create(
    Mocks.baseURL,
    {username: Mocks.username, password: Mocks.password}
  );

  describe("retrieves cids associated with user", () => {
    let cids = ref([||]);
    beforeAllPromise(() => {
      fission.cids()
      |> Js.Promise.then_(value => {
        cids := value;
        Js.Promise.resolve(());
      })
    })

    test("returns list of cids", () => {
      expect(cids^) |> toEqual(Mocks.cidList);
    })
  })

  describe("adds strings to IPFS", () => {
    let cid = ref("");
    beforeAllPromise(() => {
      fission.addString(Mocks.strContent)
      |> Js.Promise.then_(value => {
        cid := value;
        Js.Promise.resolve(());
      })
    })

    test("returns valid CID", () => {
      expect(cid^) |> toEqual(Mocks.testCID)
    })
  })

  describe("adds JSON to IPFS", () => {
    let cid = ref("");
    beforeAllPromise(() => {
      fission.add(Mocks.jsonContent)
      |> Js.Promise.then_(value => {
        cid := value;
        Js.Promise.resolve(());
      })
    })

    test("returns valid CID", () => {
      expect(cid^) |> toEqual(Mocks.testCID)
    })
  })

  describe("pins content to IPFS", () => {
    testPromise("sends request without failing", () => {
      fission.pin(Mocks.strCID)
      |> Js.Promise.then_(_value => {
        expect(true)
        |> toEqual(true)
        |> Js.Promise.resolve
      })
    })
  })

  describe("deletes content from IPFS", () => {
    testPromise("sends request without failing", () => {
      fission.pin(Mocks.strCID)
      |> Js.Promise.then_(_value => {
        expect(true)
        |> toEqual(true)
        |> Js.Promise.resolve
      })
    })
  })
})