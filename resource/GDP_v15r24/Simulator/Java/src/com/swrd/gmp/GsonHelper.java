package com.swrd.gmp;

import java.lang.reflect.Type;
import java.util.Base64;
 
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonDeserializationContext;
import com.google.gson.JsonDeserializer;
import com.google.gson.JsonElement;
import com.google.gson.JsonParseException;
import com.google.gson.JsonPrimitive;
import com.google.gson.JsonSerializationContext;
import com.google.gson.JsonSerializer;

//DLL'den byte arraye ait json de�erleri base64 string olarak gelmekte
//biz de projeye bu y�zden bir adapter ekledik
public class GsonHelper {
    public static final Gson customGson = new GsonBuilder().disableHtmlEscaping().registerTypeHierarchyAdapter(byte[].class,
            new Gmp3AdapterByteArray()).create();


    private static class Gmp3AdapterByteArray implements JsonSerializer<byte[]>, JsonDeserializer<byte[]> {
            	
    	public byte[] deserialize(JsonElement json, Type typeOfT, JsonDeserializationContext context) throws JsonParseException {
            byte[] data = Base64.getDecoder().decode(json.getAsString()); 
        	return data;
        }

        public JsonElement serialize(byte[] src, Type typeOfSrc, JsonSerializationContext context) {
            return new JsonPrimitive(Base64.getEncoder().encodeToString(src));
        }
    }
}
