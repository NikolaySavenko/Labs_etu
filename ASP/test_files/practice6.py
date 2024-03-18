import torch
from torch.utils.data import TensorDataset, DataLoader
from sklearn.datasets import make_moons
from matplotlib import pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
import numpy as np

# тут кароче скажешь с методички ктрл с ктрл в с небольшим рефакторингом(гдето большие буквы стали маленькими) ну и что добавил N и

train_on_gpu = torch.cuda.is_available()
if not train_on_gpu:
    print('CUDA is not available. Training on CPU ...')
else:
    print('CUDA is available! Training on GPU ...')
torch.cuda.is_available()


x, y = make_moons(n_samples=5000, random_state=1, noise=0.1)
plt.figure(figsize=(16, 10))
plt.title("Dataset")
plt.scatter(x[:, 0], x[:, 1], c=y, cmap="summer")
plt.show()

N = 11


x_train, x_val, y_train, y_val = train_test_split(x, y, random_state=N)


x_train_t = torch.FloatTensor(x_train)
y_train_t = torch.FloatTensor(y_train)
x_val_t = torch.FloatTensor(x_val)
y_val_t = torch.FloatTensor(y_val)
train_dataset = TensorDataset(x_train_t, y_train_t)
val_dataset = TensorDataset(x_val_t, y_val_t)
train_dataloader = DataLoader(train_dataset, batch_size=128)
val_dataloader = DataLoader(val_dataset, batch_size=128)


class LinearRegression(torch.nn.Module):
    def __init__(self, in_features: int, out_features: int, bias: bool = True):
        super().__init__()
        self.weights = torch.nn.Parameter(torch.Tensor(in_features, out_features))
        self.bias = bias
        if bias:
            self.bias_term = torch.nn.Parameter(torch.randn(out_features))

    def forward(self, x):
        x = x @ self.weights
        if self.bias:
            x += self.bias_term
        return x


linear_regression = LinearRegression(2, 1)
loss_function = torch.nn.BCEWithLogitsLoss()
optimizer = torch.optim.SGD(linear_regression.parameters(), lr=0.01 * N)
list(linear_regression.parameters())

losses = []
tol = 1e-3
max_epochs = 5 * N
prev_weights = torch.zeros_like(linear_regression.weights)
stop_it = False
for epoch in range(max_epochs):
    for it, (x_batch, y_batch) in enumerate(train_dataloader):
        optimizer.zero_grad()
        outp = linear_regression.forward(x_batch).squeeze(1)
        loss = loss_function(outp, y_batch)
        loss.backward()
        losses.append(loss.detach().flatten()[0])
        optimizer.step()
        probabilities = linear_regression.forward(x_batch)
        preds = (probabilities > 0.5).type(torch.long)
        batch_acc = (preds.flatten() == y_batch).type(torch.float32).sum() / y_batch.size(0)
        if it % 5 == 0:
            print(f"Iteration: {it + epoch * len(train_dataset)}\nBatch accuracy: {batch_acc}")
            current_weights = linear_regression.weights.detach().clone()
        if (prev_weights - current_weights).abs().max() < tol:
            print(f"\nIteration: {it + epoch * len(train_dataset)}.Convergence. Stopping iterations.")
            stop_it = True
            break
        prev_weights = current_weights
        if stop_it:
            break

plt.figure(figsize=(12, 8))
plt.plot(range(len(losses)), losses)
plt.xlabel("Iteration")
plt.ylabel("Loss")
plt.show()


def predict(dataloader, model):
    model.eval()
    predictions = np.array([])
    for x_batch, _ in dataloader:
        outp = model(x_batch)
        probs = torch.sigmoid(outp)
        preds = (probs > 0.5).type(torch.long)
        predictions = np.hstack((predictions, preds.numpy().flatten()))
        predictions = predictions
    return predictions.flatten()


print(accuracy_score(predict(val_dataloader, linear_regression), y_val))
