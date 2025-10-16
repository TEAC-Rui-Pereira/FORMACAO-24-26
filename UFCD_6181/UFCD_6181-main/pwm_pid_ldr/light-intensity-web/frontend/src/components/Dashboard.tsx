import React, { useEffect, useState } from 'react';
import { fetchLightIntensity } from '../services/api';

const Dashboard: React.FC = () => {
  const [lightIntensity, setLightIntensity] = useState<number | null>(null);

  useEffect(() => {
    const getLightIntensity = async () => {
      const intensity = await fetchLightIntensity();
      setLightIntensity(intensity);
    };

    getLightIntensity();
    const interval = setInterval(getLightIntensity, 5000); // Refresh every 5 seconds

    return () => clearInterval(interval); // Cleanup on unmount
  }, []);

  return (
    <div className="dashboard">
      <h1>Light Intensity Dashboard</h1>
      {lightIntensity !== null ? (
        <p>Current Light Intensity: {lightIntensity} lux</p>
      ) : (
        <p>Loading...</p>
      )}
    </div>
  );
};

export default Dashboard;