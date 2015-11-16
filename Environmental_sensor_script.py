import serial, datetime, ast

#from porc import Client
#
#API_KEY = "Your API Key"
## create an Orchestrate client
#client = Client(API_KEY)
#
## make sure our API key works
#client.ping().raise_for_status()

#Connect to Serial Port for communication, with timeout slightly longer than
#sensor reading delay
ser = serial.Serial('COM3', 9600, timeout=11)

#format timestamp
#timestamp = datetime.datetime.now().strftime("%Y-%m-%d" + "T" + "%H:%M:%S")

#Setup a loop to read serial data at fixed intervals
#serial data obtained from Arduino + DHT11 temperature-humidity sensor
try:
    while True:
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d" + "T" + "%H:%M:%S")
        line = ser.readline()
        #print line
        dictLine = ast.literal_eval(line)
        humidity = str(dictLine['Humidity'])
        celsius = str(dictLine['Temperature Celsius'])
        fahrenheit = str(dictLine['Temperature Fahrenheit'])
        print timestamp + "\t" + humidity + "\t" + celsius + "\t" + fahrenheit
finally:
    ser.close()
    
#transform data into new structure for POST to Socrata
timestamp = datetime.datetime.now().strftime("%Y-%m-%d" + "T" + "%H:%M:%S")

    
print timestamp + "TAB" + line

#temperature_c + ',' + time_hhmmss + ',' + date_mmddyyyy + ',' + temperature_location

#insert record
response = client.post('Temperature_Data',
                     {"location":temperature_location,
                      "date" : date_mmddyyyy,
                      "time" : time_hhmmss,
                      "value" : temperature_c})
response.raise_for_status()
print "Record inserted. Key = " + response.key
time.sleep(fixed_interval)
except ser.SerialTimeoutException:
  print('Error! Could not read the Temperature Value from unit')
  time.sleep(fixed_interval)
  