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
    plt.title("particle Energy")
    plt.hist(E)
    # Save the figure
    plt.savefig("E.png")
    plt.close()

def initialize_vectors(E, px, py, pz, pid):

    # Initialize empty list of vectors
    vector_list = []

    # The data is stored as a 2D array
    # The first index is the event number
    # The second index is the particle number

    # Therefore the individual energy can be extracted using E[event][particle]

    # Get the total number of events
    num_events = len(E)
    #print(num_events)
    # Loop over all events
    for event in range(num_events):
        # Get the total number of particles in that event
        num_particles = len(E[event])

        # Print out some useful things
        #print(num_particles)
        #print(px[event])
        if event%100==0:
            print("\tProcessing: ", event, " / ", num_events, end="\r")

        # Loop over each particle
        for particle in range(num_particles):
            #print(px[event][particle])

            ### TO DO: Write an if statement to check if the particle is a top or down-type quark based on PID

            # For now store all the particles into a vector object
            vector_list.append(vector.obj(px=px[event][particle], py=py[event][particle], pz=pz[event][particle], E=E[event][particle]))

    # Return list of vectors after for loop is finished
    return vector_list

def plot_pT_from_vectors(vectors):
    pT_list = []
    for vec in vectors:
        pT_list.append(vec.pt)
    plt.title("particle pT")
    plt.hist(ak.ravel(pT_list))
    plt.savefig("pT.png")
    plt.close()
