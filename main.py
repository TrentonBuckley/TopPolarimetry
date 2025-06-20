# Load custom functions from another file
from helper_functions import load_data, plot_hists, initialize_vectors, plot_pT_from_vectors

# The main function
def main():
    # The path to the left handed file
    path_L="hard_process_L_10k.root"
    # Extract the data
    E, px, py, pz, pid = load_data(path_L)
    # Plot the histograms
    plot_hists(E, px, py, pz, pid)
    # Load the data into vectors
    vectors = initialize_vectors(E, px, py, pz, pid)
    # Plot pT using the vector list
    plot_pT_from_vectors(vectors)

# Run this script using "python main.py" in the terminal
if __name__ == "__main__":
    main()
