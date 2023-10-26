import torch
import numpy


class MLPAgent(torch.nn.Module):
    def __init__(self, in_dim: int, out_dim: int) -> None:
        self.minx: float = -10
        self.maxx: float = 10
        self.miny: float = -10
        self.maxy: float = 10

        self.l1 = torch.nn.Linear(in_dim, 128)
        self.l2 = torch.nn.Linear(128, out_dim)

        # Activations
        self.relu = torch.relu()
        self.tanh = torch.tanh()

    @torch.no_grad()
    def forward(self, x):
        # Convert input to tensor
        xn = self.normalize(numpy.array(x))
        xt = torch.tensor(xn, dtype=torch.float32)

        z1 = self.l1(xt)
        g1 = self.relu(z1)

        z2 = self.l2(g1)
        normalized_coordinates = self.tanh(z2)

        denormalized_coordinates = self.denormalize_coordinates(normalized_coordinates.numpy())
        return denormalized_coordinates

    def normalize(self, coordinates):
        x, y, z = coordinates

        # Implement your normalization logic here, e.g., min-max normalization
        normalized_x = (x - self.minx) / (self.maxx - self.minx)
        normalized_y = (y - self.miny) / (self.maxy - self.miny)

        normalized_coordinates = (normalized_x, normalized_y)

        return normalized_coordinates

    def denormalize_coordinates(self, normalized_coordinates):
        x, y = normalized_coordinates
        denormalized_x = x * (self.max_x - self.min_x) + self.min_x
        denormalized_y = y * (self.max_y - self.min_y) + self.min_y

        denormalized_coordinates = denormalized_x, denormalized_y
        return denormalized_coordinates
