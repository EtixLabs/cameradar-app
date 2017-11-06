open Utils;

let logoImg = requireAssetURI("./images/logo.png");

type state = {server: option(Server.t)};

type action =
  | ConnectionOpened(Server.t);

let component = ReasonReact.reducerComponent("MainPage");

let make = (_children) => {
  ...component,
  didMount: (self) => {
    let onConnect = (server) => self.reduce(() => ConnectionOpened(server), ());
    let onEvent = (event) => {
      Js.log("event!");
      Js.log(event)
    };
    Server.connect(onConnect, onEvent);
    ReasonReact.NoUpdate
  },
  initialState: () => {server: None},
  reducer: (action, _state) =>
    switch action {
    | ConnectionOpened(server) => ReasonReact.Update({server: Some(server)})
    },
  render: (self) => {
    let wrapper = Glamor.(css([display("flex"), flexDirection("column"), height("100%")]));
    let topBar =
      Glamor.(
        css([
          backgroundColor("#F8F8F8"),
          borderBottom("1px solid #E8E8E8"),
          padding("15px"),
          display("flex")
        ])
      );
    let content =
      Glamor.(
        css([
          flex("1"),
          padding("30px"),
          textAlign("center"),
          display("flex"),
          flexDirection("column"),
          alignItems("center")
        ])
      );
    let logo = Glamor.(css([width("300px")]));
    <div className=wrapper>
      <div className=topBar>
        <select> <option> (textEl("Default preset")) </option> </select>
      </div>
      <div className=content>
        <img src=logoImg className=logo />
        (
          switch self.state.server {
          | Some(server) =>
            <Button onClick=((_) => Server.startScanning(server))>
              (textEl("Start cameradar"))
            </Button>
          | None => ReasonReact.nullElement
          }
        )
      </div>
    </div>
  }
};