"""
We're parsing dataset.csv as part of a pre-processing operation step
where we filter in only the necessary sensor data we require for 
the monitoring system
"""
import csv

dataset_name='dataset.csv'
output_prefix='dataset-'
vehicle_sensors = ['Fuel_Consumption', 'Engine_speed', 'Engine_Coolant_Temperature', 'Current_Gear', 'Vehicle_speed']

with open(dataset_name, 'r') as f:
    reader = csv.DictReader(f)

    rows = [x for x in reader]
    columns = [x for x in rows[0].keys() if x in vehicle_sensors]

print(columns)

for col in columns:
    fname = output_prefix+col+'.txt'
    print('Writing to ', fname)
    with open(fname, 'w', newline='') as f:
        writer = csv.writer(f)
        for row in rows:
            line = [row[col]]
            writer.writerow(line)
