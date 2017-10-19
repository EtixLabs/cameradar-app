open Utils;

requireCSS("./MainWindow.css");

let logo = requireAssetURI("./images/logo.png");

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
  render: (self) =>
    <div className="mainWindow">
      (
        switch self.state.server {
        | Some(server) =>
          <button onClick=((_) => Server.startScanning(server))>
            (textEl("Start scanning !"))
          </button>
        | None => ReasonReact.nullElement
        }
      )
    </div>
};