#include "MenuSystem.h"
#include <algorithm>

void MenuSystem::menu() {
  int tape_length = 0; // length
  TuringTape tape(-1);
  int num_steps = 0; // number of steps
  TuringMachine *machine = nullptr;
  int nowState = 0; // current state
  int steps_No = 1;
  std::cout << "How long should the tape be? " << std::endl;
  // Get the tape_length
  while (!(std::cin >> tape_length) || (tape_length < 0 && tape_length != -1)) {
    std::cout << "How long should the tape be? " << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  tape = TuringTape(tape_length);
  while (true) {
    show_chosen();
    std::cout << "enter option " << std::endl;
    std::string choice;
    std::cin >> choice;
    if (choice == "1") {
      std::cout << "What is the maximum state and what is the maximum content?"
                << std::endl;
      int start_state, num_states;
      while (!(std::cin >> start_state >> num_states) ||
             ((start_state < 0 && start_state != -1) ||
              (num_states < 0 && num_states != -1))) {
        std::cout
            << "What is the maximum state and what is the maximum content?"
            << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      machine = new DenseTuringMachine(start_state, num_states);
    } else if (choice == "2") {
      machine = new SparseTuringMachine();

    } else if (choice == "3") {
      if (machine == nullptr) {
        continue;
      }
      std::cout << "What state do you wish to add?" << std::endl;
      TuringMachineState state;
      while (!(std::cin >> state) || (state.getMoveDirection() != "<-" &&
                                      state.getMoveDirection() != "->")) {
        std::cout << "What state do you wish to add?" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      machine->add(state);
    } else if (choice == "4") {
      if (machine == nullptr) {
        continue;
      }
      machine = createDenseTuringMachine(*machine->getAll());
    } else if (choice == "5") {
      if (machine == nullptr) {
        continue;
      }

      std::cout << "How many steps do you wish to execute?" << std::endl;
      int t;

      while (!(std::cin >> t) || (t <= 0 && t != -1)) {
        std::cout << "How many steps do you wish to execute?" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      if (t == -1) {
        num_steps = INT32_MAX;
      } else {
        if (num_steps != INT32_MAX)
          num_steps += t;
      }

      while (steps_No <= num_steps) {
        if (!tape.isFine()) {
          std::cout << "In step " << steps_No << ", the position is "
                    << tape.getPosition() << ", but that is outside the tape."
                    << std::endl;
          break;
        }
        TuringMachineState *nowStatePtr;
        nowStatePtr = machine->find(nowState, tape.getContent());
        // if not found
        if (nowStatePtr == nullptr) {
          std::cout << "In step " << steps_No
                    << ", there is no Turing machine state with state "
                    << nowState << " and content " << tape.getContent()
                    << std::endl;
          break;
        }
        nowState = nowStatePtr->getNextState();
        tape.setContent(nowStatePtr->getNextContent());
        if (nowStatePtr->getMoveDirection() == "->")
          tape.moveRight();
        else if (nowStatePtr->getMoveDirection() == "<-")
          tape.moveLeft();
        steps_No++;
      }
    } else if (choice == "6") {
      std::cout << "The current state is " << nowState << "." << std::endl
                << "The current position is " << tape.getPosition() << "."
                << std::endl;
      std::cout << "The content of the tape is " << tape << "." << std::endl
                << "The Turing machine has states:";
      auto status = *machine->getAll();
      for (int i = 0; i < status.size(); i++) {
        std::cout << "<" << status[i] << ">";
        if (i != status.size() - 1)
          std::cout << " ";
      }
      std::cout << std::endl;
    } else if (choice == "q" || choice == "Q") {
      break;
    }
  }
}

// show the menu detail
void MenuSystem::show_chosen() {
  std::cout << "1. Create dense Turing machine\n"
            << "2. Create sparse Turing machine\n"
            << "3. Add state to Turing machine\n"
            << "4. Compact Turing machine\n"
            << "5. Execute Turing machine\n"
            << "6. Output current information\n"
            << "write Q or q to quit" << std::endl;
}

// Helper function to sort and rename states/contents
void renameStatesAndContents(std::vector<TuringMachineState> &states,
                             std::map<int, int> &state_map,
                             std::map<int, int> &content_map) {
  // Sort states and contents
  std::vector<int> unique_states;
  std::vector<int> unique_contents;
  for (const TuringMachineState &s : states) {
    unique_states.push_back(s.getCurrentState());
    unique_contents.push_back(s.getCurrentContent());
    unique_states.push_back(s.getNextState());
    unique_contents.push_back(s.getNextContent());
  }
  std::sort(unique_states.begin(), unique_states.end());
  std::sort(unique_contents.begin(), unique_contents.end());
  unique_states.erase(std::unique(unique_states.begin(), unique_states.end()),
                      unique_states.end());
  unique_contents.erase(
      std::unique(unique_contents.begin(), unique_contents.end()),
      unique_contents.end());

  // Rename states and contents
  for (int i = 0; i < (int)unique_states.size(); i++) {
    state_map[unique_states[i]] = i;
  }
  for (int i = 0; i < (int)unique_contents.size(); i++) {
    content_map[unique_contents[i]] = i;
  }
}

// Helper function to create a DenseTuringMachine from a vector of
// TuringMachineStates
TuringMachine *
createDenseTuringMachine(std::vector<TuringMachineState> &states) {
  std::map<int, int> state_map;
  std::map<int, int> content_map;

  // Rename states and contents
  renameStatesAndContents(states, state_map, content_map);

  // Create DenseTuringMachine
  TuringMachine *dtm =
      new DenseTuringMachine(state_map.size() - 1, content_map.size() - 1);
  for (const TuringMachineState &s : states) {
    int current_state = state_map[s.getCurrentState()];
    int current_content = content_map[s.getCurrentContent()];
    int next_state = state_map[s.getNextState()];
    int new_content = content_map[s.getNextContent()];
    TuringMachineState temp(current_state, current_content, next_state,
                            new_content, s.getMoveDirection());
    dtm->add(temp);
  }

  return dtm;
}