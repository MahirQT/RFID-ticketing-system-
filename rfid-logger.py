import serial
import csv
from datetime import datetime
import time

# Configuration
SERIAL_PORT = 'COM7'  # Change to your Arduino port
BAUD_RATE = 9600
VALID_CSV = "valid_transactions.csv"
INVALID_CSV = "invalid_cards.csv"

# Headers for CSV files
VALID_HEADERS = ["Timestamp", "Name", "Fee (Rs)", "Balance (Rs)", "UID", "Event"]
INVALID_HEADERS = ["Timestamp", "UID", "Error"]

def setup_csv():
    """Create CSV files with headers if they don't exist."""
    for filename, headers in [(VALID_CSV, VALID_HEADERS), (INVALID_CSV, INVALID_HEADERS)]:
        with open(filename, 'a', newline='', encoding='utf-8') as file:
            writer = csv.writer(file)
            if file.tell() == 0:
                writer.writerow(headers)

def log_valid(data):
    """Log valid transactions (exits)."""
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    with open(VALID_CSV, 'a', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow([timestamp] + data)
    print(f"[VALID] {timestamp} | {' | '.join(data)}")

def log_invalid(uid):
    """Log invalid card attempts."""
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    with open(INVALID_CSV, 'a', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow([timestamp, uid, "INVALID_CARD"])
    print(f"[INVALID] {timestamp} | UID: {uid}")

def parse_serial_line(line):
    """Parse Arduino's serial output."""
    return [item.strip() for item in line.split(',')]

def main():
    setup_csv()
    print(f"Logging valid transactions to {VALID_CSV}")
    print(f"Logging invalid cards to {INVALID_CSV}")
    print("Press Ctrl+C to stop.\n")

    try:
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
            while True:
                if ser.in_waiting > 0:
                    line = ser.readline().decode('utf-8').strip()
                    if line:
                        if "INVALID" in line:  # Detect invalid cards
                            uid = line.split(':')[-1].strip()
                            log_invalid(uid)
                        else:  # Process valid transactions
                            data = parse_serial_line(line)
                            if "EXIT" in data:  # Only log exits (not entries)
                                log_valid(data)
    except KeyboardInterrupt:
        print("\nStopping logger...")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()