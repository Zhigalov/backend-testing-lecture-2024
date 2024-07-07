def test_hello_world():
    assert 2 + 2 == 4

async def test_calculate(mockserver, service_client, load_json):
    @mockserver.handler('/delivery/calculate')
    async def mock(request):
        assert request.json['route_points'] == [
            {'lat': 11.11, 'lon': 22.22},
            {'lat': 33.33, 'lon': 44.44}
        ]
        return mockserver.make_response(
            json=load_json('delivery_response.json')
        )

    response = await service_client.post(
        '/v1/calculate',
        params={
            'a_lat': 11.11,
            'a_lon': 22.22,
            'b_lat': 33.33,
            'b_lon': 44.44,
        })
    assert response.status == 200
    assert response.text == '356 рублей'