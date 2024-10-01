from flask import Flask,request
import pickle

with open('model.pkl','rb') as model:
    ai = pickle.load(model)

app = Flask(_name_)

@app.route('/predict',methods = ['GET','POST'])
def predict():
    h = float(request.args.get('h'))
    t = float(request.args.get('t'))
    result = ai.predict([[h,t]])[0]
    return result