import React, { useEffect, useState } from "react";
import { db } from "./firebaseConfig";
import { ref, onValue } from "firebase/database";
import { Line } from "react-chartjs-2";

function App() {
  const [flowRate, setFlowRate] = useState(0);
  const [history, setHistory] = useState([]);

  useEffect(() => {
    const flowRef = ref(db, "school1/flowRate");

    onValue(flowRef, (snapshot) => {
      const rate = snapshot.val();
      setFlowRate(rate);
      setHistory((prev) => [...prev.slice(-19), rate]);
    });
  }, []);

  return (
    <div className="App">
      <h2>💧 Smart Water Monitor</h2>
      <h3>Current Flow Rate: {flowRate.toFixed(2)} L/min</h3>

      <Line
        data={{
          labels: history.map((_, i) => i + 1),
          datasets: [
            {
              label: "Flow Rate (L/min)",
              data: history,
              borderColor: "blue",
              fill: false,
            },
          ],
        }}
      />
    </div>
  );
}

export default App;