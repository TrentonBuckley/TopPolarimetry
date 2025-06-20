import uproot
import vector
import awkward as ak
import matplotlib.pyplot as plt

# Function that takes the file path and loads relevent data
def load_data(path):
    # Uses uproot to load data
    with uproot.open(path+":events") as f:
        # Optionally print all available variables within the file
        #print(f.keys())
        # Extract E, px, py, pz, and pid
        E = f['energy'].array()
        px = f['px'].array()
        py = f['py'].array()
        pz = f['pz'].array()
        pid = f['pid'].array()

    # The function returns relevent variables
    return E, px, py, pz, pid

# Function that takes the input data and plots simple hist
def plot_hists(E, px, py, pz, pid):
    # "Flatten" the data
    E = ak.ravel(E)
    # Plot a histogram
    plt.hist(E)
    # Save the figure
    plt.savefig("E.png")

def initialize_vectors(E, px, py, pz, pid):
    pass
