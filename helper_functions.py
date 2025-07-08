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

def select_top(E, px, py, pz, pid):
    mask = pid==6
    return E[mask], px[mask], py[mask], pz[mask]
    
def select_down_type(E, px, py, pz, pid):
    mask1 = pid==1
    mask2 = pid==3
    mask = mask1 | mask2
    return E[mask], px[mask], py[mask], pz[mask]

# Function that takes the input data and plots simple hist
def plot_hists(title, var):
    # "Flatten" the data
    var = ak.ravel(var)
    # Plot a histogram
    plt.title(title)
    plt.hist(var, bins=50)
    # Save the figure
    plt.savefig(title+".png")
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

            # Store all the particles into a vector object
            vector_list.append(vector.obj(px=px[event][particle], py=py[event][particle], pz=pz[event][particle], E=E[event][particle]))

    # Return list of vectors after for loop is finished
    return vector_list

def plot_mass_from_vectors(title, vectors):
    m_list = []
    for vec in vectors:
        m_list.append(vec.m)
    plt.title(title)
    plt.hist(ak.ravel(m_list),bins=30)
    plt.savefig(title+".png")
    plt.close()
