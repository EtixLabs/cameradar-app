module MessageEvent = {
  type t;
  [@bs.get] external data : t => string = "";
};

type t;

[@bs.scope "window"] [@bs.new] external create_ws : string => t = "WebSocket";

[@bs.set] external onMsg : (t, MessageEvent.t => unit) => unit = "onmessage";

[@bs.set] external onOpen : (t, unit => unit) => unit = "onopen";

[@bs.send] external send : (t, string) => unit = "";

[@bs.set] external onError : (t, unit => unit) => unit = "onerror";

[@bs.set] external onClose : (t, unit => unit) => unit = "onclose";

let onMsg = (ws, cb) => onMsg(ws, (ev) => MessageEvent.data(ev) |> cb);