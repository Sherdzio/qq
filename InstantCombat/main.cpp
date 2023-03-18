#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <thread>
#include <Api.h>
#include <pybind11/embed.h>
namespace py = pybind11;

using namespace std;

std::vector<std::pair<std::string, int>> returnAllPorts() {
    py::object py_module = py::module::import("Api");
    py::object py_function = py_module.attr("returnAllPorts");
    py::list py_ports = py_function();
    std::vector<std::pair<std::string, int>> ports;
    for (size_t i = 0; i < py_ports.size(); ++i) {
        std::string name = py::str(py_ports[i].attr("first"));
        int port = py::int_(py_ports[i].attr("second"));
        ports.push_back(std::make_pair(name, port));
    }
    return ports;
}

int returnCorrectPort(const std::string& playerName) {
    py::object py_module = py::module::import("Api");
    py::object py_function = py_module.attr("returnCorrectPort");
    py::int_ py_port = py_function(playerName);
    return int(py_port);
}

bool enable_phoenixbot = false;

void toggle_phoenixbot() {
    enable_phoenixbot = !enable_phoenixbot;
}

void run_character(const std::string& character_name, int port, bool move_to_point, bool is_stationary, int x_coordinate, int y_coordinate) {
    PhoenixAPI api(port);

    while (true) {
        if (!enable_phoenixbot) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        if (move_to_point && is_stationary) {
            api.walk_to_point(x_coordinate, y_coordinate);
        }
        else {
            // Wykonaj inne czynnoœci dla pozosta³ych postaci
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> delay(200, 450);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay(gen)));
    }
}

int main() {
    py::scoped_interpreter guard{};
    std::vector<std::pair<std::string, int>> ports = returnAllPorts();

    for (const auto& port : ports) {
        std::cout << "Name: " << port.first << " Port: " << port.second << std::endl;
    }

    std::map<std::string, bool> character_types;
    std::map<std::string, int> character_x_coordinates;
    std::map<std::string, int> character_y_coordinates;

    // Tutaj mo¿esz zainicjowaæ wartoœci dla postaci

    while (true) {
        char input;
        std::cin.get(input);

        if (input == ';') {
            toggle_phoenixbot();
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}