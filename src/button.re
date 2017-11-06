let component = ReasonReact.statelessComponent("Button");

let make = (~onClick, children) => {
  ...component,
  render: (_self) => {
    let style =
      Glamor.(
        css([
          marginTop("30px"),
          fontSize("18px"),
          backgroundColor("#46AC1D"),
          borderRadius("5px"),
          color("#ffffff"),
          border("none"),
          padding("20px 30px"),
          outline("none"),
          cursor("pointer")
        ])
      );
    ReasonReact.createDomElement(
      "button",
      ~props={"className": style, "onClick": onClick},
      children
    )
  }
};