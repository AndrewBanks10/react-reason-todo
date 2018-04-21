type item = {
  id: int,
  title: string,
  completed: bool
};

let lastId = ref(0);
let newItem = (text) => {
  lastId := lastId^ + 1;
  {id: lastId^, title: text, completed: false}
};

let component = ReasonReact.statelessComponent("TodoItem");
let make = (~item, ~onToggle, ~onDelete, _children) => {
  ...component,
  render: (_) =>
    <div>
      <div className="item" onClick=((_evt) => onToggle())>
        <input className="ItemCheck"
          _type="checkbox"
          checked=(Js.Boolean.to_js_boolean(item.completed))
        />
        <div className="ItemText">
            (ReasonReact.stringToElement(item.title))
        </div>
        <div className="ItemDelete" onClick=((_evt) => onDelete())>(ReasonReact.stringToElement("X"))</div>
      </div>
    </div>
};
