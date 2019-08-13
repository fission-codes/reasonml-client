open Jest;

[@bs.val] external baseURL: string = "process.env.INTERPLANETARY_FISSION_URL";
[@bs.val] external username: string = "process.env.INTERPLANETARY_FISSION_USERNAME";
[@bs.val] external password: string = "process.env.INTERPLANETARY_FISSION_PASSWORD";

let randomString() = "10osidfjpaeoi4j"

describe("Fission.Simple", () => {
    open Expect;
    let str = randomString();
    let cid = ref("");

    beforeAllPromise(() => {
        Fission.addStr(baseURL, {username, password}, str)
        |> Js.Promise.then_(value => {
            Js.Console.log("IN PROMISE: " ++ value)
            cid := value;
            Js.Promise.resolve(value);
        })
    })

    test("filler", () => {
        Js.Console.log("HERE: " ++ cid^)
        expect("1234") |> toEqual("1234")
    })
})