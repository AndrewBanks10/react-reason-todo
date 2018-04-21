/* 
  TodoApp component state definition and initial values
*/
type state = {
  items: list(TodoItem.item)
};
let initialState = () => {
  items: []
};

/* 
  TodoApp component reducers
*/
type action =
  | AddItem(string)
  | ToggleItem(int)
  | DeleteItem(int);

let reducer = (action, {items}) =>
  switch action {
    | AddItem(text) => ReasonReact.Update({items: [TodoItem.newItem(text), ...items]})
    | ToggleItem(id) =>
      let items =
        List.map(
          (item) =>
          item.TodoItem.id === id ?
              {...item, completed: ! item.completed} : item,
          items
        );
      ReasonReact.Update({items: items})
    | DeleteItem(id) =>
      let items =
        List.filter(
          (item) =>
            (item.TodoItem.id !== id),
          items
        );
      ReasonReact.Update({items: items})
  };

/*
  TodoApp component
*/
let component = ReasonReact.reducerComponent("TodoApp");
let make = (_children) => {
  ...component,
  initialState,
  reducer,
  render: ({state: {items}, reduce}) => {
    <div className="app">
      <div className="title">
        (ReasonReact.stringToElement("What to do"))
        <Input onSubmit=(reduce((text) => AddItem(text))) />
      </div>
      <div className="items">
        (
          ReasonReact.arrayToElement(Array.of_list(List.map(
            (item) =>
              <TodoItem
                key=(string_of_int(item.TodoItem.id))
                onToggle=(reduce(() => ToggleItem(item.id)))
                onDelete=(reduce(() => DeleteItem(item.id)))
                item
              />,
            items
          )))
        )
      </div>
      <div className="footer">
        (ReasonReact.stringToElement(string_of_int(List.length(items)) ++ " items"))
      </div>
    </div>
  }
};
