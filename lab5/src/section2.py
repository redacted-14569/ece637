import numpy as np 
import matplotlib.pyplot as plt 
from matplotlib import colormaps 
import matplotlib
from PIL import Image
import sys
from utils import plot_data, gen, estParams, decorr, whiten

if __name__== '__main__':
    #2.1
    N=1000
    R=np.array([[2, -1.2],[-1.2, 1]])
    dim=R.shape[0]
    D, V = np.linalg.eig(R)
    W = np.random.randn(dim, N)
    X_tilde=np.diag(np.sqrt(D)) @ W
    X = V @ X_tilde
    for data, title, char in list(zip([W, X_tilde, X], [r'$W$', r'$\tilde{X}$', r'$X$'], ['w', 'xt', 'x'])):
        plot_data(data, title, char)

    # 2.2 
    X=gen(R, N=N)
    Rhat, mhat=estParams(X)
    X_tilde=decorr(X, R)
    W=whiten(X, R)
    R_w_hat, m_w_hat = estParams(W)
    print("R_W: "+str(R_w_hat))
    print("Mu_W: "+str(m_w_hat))
    for data, title, char in list(zip([W, X_tilde, X], [r'$W$', r'$\tilde{X}$', r'$X$'], ['w_hat', 'xt_hat', 'x_hat'])):
        plot_data(data, title, char)
