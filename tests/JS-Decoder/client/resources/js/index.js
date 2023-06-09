const dirname = window.location.pathname.replace('/index.html', '');
;
const encoded_data_url = window.location.origin + dirname + "/resources/assets/encoded_data.bin";

function loadEncodedFile() {
    return axios.get(encoded_data_url, {responseType: 'arraybuffer'})
        .then(response => response.data);
}

class CandleStick {
    id;
    timestamp;
    open;
    high;
    low;
    close;
    Volume_BTC;
    Volume_USD;
}

candles=[];

function OnDecodedCandles(){
    console.log("id: "+candles[0].id)
    CreateTable();
}

Module.onRuntimeInitialized = _ => {
    const api = {
        test_print: Module.cwrap('test_print'),
        message: Module.cwrap('getAMessage', 'string', []),
        // const char* template_xml, uint8_t encoded_data[]
        Decode: Module.cwrap('Decode', 'number', ['string', 'number', 'number', 'number']),
    };

    loadEncodedFile().then((buffer) => {
        const encoded_data = new Uint8Array(buffer);

        // Allocate memory in the Emscripten heap
        const encoded_data_ptr = Module._malloc(encoded_data.length);
        // Set the values in the allocated memory
        Module.HEAP8.set(encoded_data, encoded_data_ptr);

        // Allocate memory in the Emscripten heap
        const decoded_data_ptr = Module._malloc(1000*28);

        no_of_fields = 7;
        size = api.Decode(candle_xml, encoded_data_ptr, encoded_data.length, decoded_data_ptr);

        let my_uint32_buffer = new Uint32Array(Module.HEAP32.buffer, decoded_data_ptr, size*28);

        for (let i = 0; i < 1000; i++) {
            let candle = new CandleStick();
            candle.id = my_uint32_buffer[7*i];
            candle.open = my_uint32_buffer[7*i+1];
            candle.high = my_uint32_buffer[7*i+2];
            candle.low = my_uint32_buffer[7*i+3];
            candle.close = my_uint32_buffer[7*i+4];
            candle.Volume_BTC = my_uint32_buffer[7*i+5];
            candle.Volume_USD = my_uint32_buffer[7*i+6];
            candles.push(candle)


        }

        OnDecodedCandles()

        // Free the allocated memory
        Module._free(encoded_data_ptr);
        Module._free(decoded_data_ptr);
    })
};