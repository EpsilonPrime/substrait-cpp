class PlanLoader {
    public enum PlanFileFormat {
        BINARY(0),
        JSON(1),
        PROTOTEXT(2),
        TEXT(3);

        private final int value;

        PlanFileFormat(int value) {
            this.value = value;
        }

        public int getValue() {
            return this.value;
        }
    }

    public native byte[] loadSubstraitPlan(String filename);
    public native void saveSubstraitPlan(byte[] planData, String filename, int format);

    // MEGAHACK -- Add conversion from Plan to byte[].
}

public class Hello {
    public static void main(String[] args) {
        System.loadLibrary("planloader_jni");
        byte[] planData = PlanLoader().loadSubstraitPlan("myplan.json");
        saveSubstraitPlan(planData, "output.splan", 3);
    }
}
