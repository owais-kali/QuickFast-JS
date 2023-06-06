Module.onRuntimeInitialized = _ => {
    const api = {
        test_print: Module.cwrap('test_print'),
        message: Module.cwrap('getAMessage', 'string', []),
        test: Module.cwrap('test', 'string', []),
    };
    console.log(api.test());
};

console.log("candle_xml: "+candle_xml)