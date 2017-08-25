import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn import metrics
from sklearn import linear_model

sales = pd.read_csv("home_data.csv")

plt.plot(sales['sqft_living'], sales['price'], 'bo')
plt.title("Scatter Plot")
plt.ylabel("price")
plt.xlabel("sqft_living")
plt.show()

print("zipcode 98039 price mean: ", sales[sales.zipcode == 98039]['price'].mean())

np.random.seed(0)
msk = np.random.rand(len(sales)) <= 0.8
train_data, test_data = sales[msk], sales[~msk]

# Build the regression model using only sqft_living as a feature

train_data_X = train_data['sqft_living'].values.reshape(len(train_data['sqft_living']), 1)
train_data_Y = train_data['price'].values.reshape(len(train_data['price']), 1)
test_data_X = test_data['sqft_living'].values.reshape(len(test_data['sqft_living']), 1)
test_data_Y = test_data['price'].values.reshape(len(test_data['price']), 1)

sqft_model = linear_model.LinearRegression()
sqft_model.fit(train_data_X, train_data_Y)

print('sqft_model rmse: ', np.sqrt(metrics.mean_squared_error(test_data_Y, sqft_model.predict(test_data_X))))

plt.plot(test_data['sqft_living'], test_data['price'], '.',
         test_data['sqft_living'], sqft_model.predict(test_data_X), '-')
plt.show()
print('sqft_living coefficients: ', sqft_model.coef_[0][0])

# Build a regression model with more features
features = ['bedrooms', 'bathrooms', 'sqft_living', 'sqft_lot', 'floors', 'zipcode']
train_data_X = np.hstack(tuple([train_data[x].values.reshape(len(train_data[x]), 1) for x in features]))
test_data_X = np.hstack(tuple([test_data[x].values.reshape(len(test_data[x]), 1) for x in features]))

my_features_model = linear_model.LinearRegression().fit(train_data_X, train_data_Y)
print('my_features_model rmse: ',
      np.sqrt(metrics.mean_squared_error(test_data_Y, my_features_model.predict(test_data_X))))
plt.plot(test_data['sqft_living'], test_data['price'], '.',
         test_data['sqft_living'], my_features_model.predict(test_data_X), '-')
plt.show()
print('my_features_model coefficients: ')
for i in zip(my_features_model.coef_[0], features):
    print(i)


# Apply learned models to predict prices of 3 houses
house1 = sales[sales.id == 5309101200]
print("house1: ", house1['price'])
print("sqft_model: ", sqft_model.predict(house1['sqft_living'].values.reshape(len(house1['sqft_living']), 1))[0][0])
print("my_features_model: ",
      my_features_model.predict(
          np.hstack(tuple([house1[x].values.reshape(len(house1[x]), 1) for x in features])))[0][0])

house2 = sales[sales.id == 1925069082]
print("house2: ", house2['price'])
print("sqft_model: ", sqft_model.predict(house2['sqft_living'].values.reshape(len(house2['sqft_living']), 1))[0][0])
print("my_features_model: ",
      my_features_model.predict(
          np.hstack(tuple([house2[x].values.reshape(len(house2[x]), 1) for x in features])))[0][0])


house3 = np.array([8, 25, 50000, 225000, 4, 98039]).reshape((1, 6))
print("house3 my_features_model: ", my_features_model.predict(house3)[0][0])
