import pandas as pd

from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score


start_table = pd.read_csv("../diabetes_data_upload.csv")
X = start_table.iloc[:, 0:-1].values
print('start data(x): ', X)
Y = start_table["class"].values
print('end data(y): ', Y)

enc = preprocessing.OneHotEncoder()
enc.fit(X)
X = enc.transform(X).toarray()

X = preprocessing.scale(X)
print('standardize data(x): ', X)


N = 11
X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.8, random_state=N)
print('x train', X_train.shape)
print('x test', X_test.shape)
print('y train', Y_train.shape)
print('y test', Y_test.shape)

best_acc = 0
best_c = 0
for current_c in [100, 10, 1, 0.1, 0.01, 0.001]:
    model = LogisticRegression(random_state=N, C=current_c).fit(X_train, Y_train)
    Y_predict = model.predict(X_test)
    current_acc = accuracy_score(Y_test, Y_predict)
    if best_acc < current_acc:
        best_acc = current_acc
        best_c = current_c
    print(f"c = {current_c}, accuracy: {current_acc}")

print(f"\nbest accuracy {best_acc}; best c = {best_c}")
