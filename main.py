# Load custom functions from another file
from helper_functions import *


# The main function
def main():
    # The path to the left handed file
    path_L="hard_process_L_10k.root"
    E, px, py, pz, pid, status = load_data(path_L)

    E_top, px_top, py_top, pz_top = select_top(E, px, py, pz, pid)
    plot_hists("Top E", E_top)
    top_vectors = initialize_vectors(E_top, px_top, py_top, pz_top, pid)
    plot_mass_from_vectors("Top Mass", top_vectors)

    E_down, px_down, py_down, pz_down = select_down_type(E, px, py, pz, pid, status)
    print(len(E_down))
    plot_hists("Down E", E_down)
    #down_vectors = initialize_vectors(E_down, px_down, py_down, pz_down, pid)
    #plot_mass_from_vectors("Down Type Mass", down_vectors)

# Run this script using "python main.py" in the terminal
if __name__ == "__main__":
    main()
