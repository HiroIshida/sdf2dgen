import numpy as np
import matplotlib.pyplot as plt
from pysdf2d import compute_sdf

verts1 = [
        [0.1, 0.1],
        [0.9, 0.1],
        [0.9, 0.9],
        [0.1, 0.9],
        [0.1, 0.8],
        [0.8, 0.8],
        [0.8, 0.2],
        [0.1, 0.2],
        ]

verts2 = [
        [0.5, 0.4],
        [0.6, 0.5],
        [0.5, 0.6],
        [0.4, 0.5],
        ]

mat = compute_sdf([0, 0], [1, 1], 101, 101, [verts1, verts2], True)
plt.imshow(mat)
plt.show()
