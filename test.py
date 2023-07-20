import requests

def send_get_request():
    url = 'http://localhost:8091'  # Substitua pela URL do seu servidor
    response = requests.get(url)
    print(f'Status Code: {response.status_code}')
    print(f'Response Content: {response.text}')

if __name__ == "__main__":
    send_get_request()
