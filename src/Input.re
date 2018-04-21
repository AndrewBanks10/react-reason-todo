
let valueFromEvent = (evt) : string => (
  evt
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;

/* 
  Component state definition and initial values
*/
type state = {
  text: string,
  error: string
};
let initialState = () => ({text: "", error: ""});

/* 
  Component reducers
*/
type action =
  | ChangeText(string)
  | SetError(string);

let reducer = (action, _state) =>
  switch (action) {
    | ChangeText(text) => ReasonReact.Update({text, error: ""})
    | SetError(error) => ReasonReact.Update({text: "", error})
  };

let maxItemSize = 30;
/* Perform a validation and submit if appropriate */
let validateAndSubmit = (text, reduce, onSubmit) => {
  let len = Js.String.length(text);
  if ( len === 0 ) {
    (reduce(() => SetError("Empty todo is invalid.")))()
  } else if ( len >= maxItemSize ) {
    (reduce(() => SetError("Todos are limited to 30 characters.")))()
  } else {
    onSubmit(text);
    (reduce(() => ChangeText("")))()
  }
};

let component = ReasonReact.reducerComponent("Input");
let make = (~onSubmit, _) => {
  ...component,
  initialState,
  reducer,
  render: ({state: {text, error}, reduce}) =>
    <div>
      <input
        value=text
        _type="text"
        placeholder="Write something to do"
        onChange=(reduce(evt => ChangeText(valueFromEvent(evt))))
        onKeyDown=(evt => ReactEventRe.Keyboard.key(evt) === "Enter" ?
            validateAndSubmit(text, reduce, onSubmit) : ()
        )
      />
      <div className="error">(ReasonReact.stringToElement(error))</div>
    </div>
};
