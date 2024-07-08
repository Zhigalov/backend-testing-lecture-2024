import re
import requests


def test_calculate():
  response = requests.post(
    'http://localhost:8080/v1/calculate'
    '?a_lat=56.843427&a_lon=60.629445'
    '&b_lat=56.835485&b_lon=60.591105')
  assert response.status_code == 200
  assert response.text == '500 рублей'


def test_calculate_re():
  response = requests.post(
    'http://localhost:8080/v1/calculate'
    '?a_lat=56.843427&a_lon=60.629445'
    '&b_lat=56.835485&b_lon=60.591105')
  pattern = re.compile(r'\d+ рубл[ь|я|ей]')

  assert response.status_code == 200
  assert re.search(pattern, response.text) is not None

  # pytest backend-testing-lecture-2024/acceptance