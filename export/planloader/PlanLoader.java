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

    private native byte[] loadSubstraitPlan(String filename);
    private native void saveSubstraitPlan(byte[] planData, String filename, int format);

    // MEGAHACK -- Document including the fact that it throws an exception.
    public byte[] loadPlan(String filename) {
      // MEGAHACK -- Add conversion from byte[] to Plan.
      return loadSubstraitPlan(filename);
    }

    // MEGAHACK -- Document including the fact that it throws an exception.
    public void savePlan(byte[] planData, String filename, PlanFileFormat format) {
      // MEGAHACK -- Add conversion from Plan to byte[].
      return saveSubstraitPlan(planData, filename, format.getValue());
    }
}

public class Hello {
    public static void main(String[] args) {
        System.loadLibrary("planloader_jni");
        byte[] planData = PlanLoader().loadPlan("myplan.json");
        savePlan(planData, "output.splan", PlanLoader.PlanFileFormat.TEXT);
    }
}
