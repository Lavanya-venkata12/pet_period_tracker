import serial
import time
import pandas as pd


ser = serial.Serial("COM5",115200,timeout = 0.5)

dataset =[]
count=0

while True:
    if(ser.inWaiting() > 0):
        data=ser.readline()
        data=data.decode('utf-8')
        if(data.startswith('#')):

            data = data [ :-1]
            data = data.split(',')
            count+=1
            dummy=[float(data[1]),float(data[2]),float(data[3]),data[4]]
            dataset.append(dummy)
            if(count==50):
                df=pd.DataFrame(dataset)
                df.to_csv('project4.csv')
                count=0
            print(dataset)



