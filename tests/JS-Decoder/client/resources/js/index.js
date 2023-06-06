Module.onRuntimeInitialized = _ => {
    const api = {
        test_print: Module.cwrap('test_print'),
        message: Module.cwrap('getAMessage', 'string', []),
        // const char* template_xml, uint8_t encoded_data[]
        Decode: Module.cwrap('Decode', 'string', ['string', 'number', 'number']),
    };

    // Allocate memory in the Emscripten heap
    const arrayPtr = Module._malloc(encoded_data.length); // Assuming 4 bytes per integer

    // Set the values in the allocated memory
    Module.HEAP8.set(encoded_data, arrayPtr);

    console.log(api.Decode(candle_xml, arrayPtr, encoded_data.length));

    // Free the allocated memory
    Module._free(arrayPtr);
};