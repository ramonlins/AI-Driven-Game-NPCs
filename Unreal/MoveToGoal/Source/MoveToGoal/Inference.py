import torch
import numpy
import pdb


class MLPAgent(torch.nn.Module):
    def __init__(self, in_dim: int, out_dim: int) -> None:
        super(MLPAgent, self).__init__()

        shift_mod: int = 5
        self.minx: float = -shift_mod
        self.maxx: float = shift_mod
        self.miny: float = -shift_mod
        self.maxy: float = shift_mod
        self.minz: float = 0
        self.maxz: float = 32

        self.l1 = torch.nn.Linear(in_dim, 128)
        self.l2 = torch.nn.Linear(128, out_dim)

        # Activations
        self.relu = torch.nn.ReLU()
        self.tanh = torch.nn.Tanh()

    @torch.no_grad()
    def forward(self, x):
        # Convert input to tensor
        xn = self.normalize(numpy.array(x))
        xt = torch.tensor(xn, dtype=torch.float32)

        z1 = self.l1(xt)
        g1 = self.relu(z1)

        z2 = self.l2(g1)
        normalized_coordinates = self.tanh(z2)

        return self.denormalize_coordinates(normalized_coordinates.numpy())

    def normalize(self, coordinates):
        x, y, z = coordinates

        # Implement your normalization logic here, e.g., min-max normalization
        normalized_x = (x - self.minx) / (self.maxx - self.minx)
        normalized_y = (y - self.miny) / (self.maxy - self.miny)
        normalized_z = (z - self.minz) / (self.maxz - self.minz)

        return normalized_x, normalized_y, normalized_z

    def denormalize_coordinates(self, normalized_coordinates):
        x, y = normalized_coordinates
        denormalized_x = x * (self.maxx - self.minx) + self.minx
        denormalized_y = y * (self.maxy - self.miny) + self.miny

        return denormalized_x, denormalized_y
