import React, { useState, useEffect } from 'react';
import { fetchLightIntensity, updateLightIntensity } from '../services/api';

const LightControl: React.FC = () => {
  const [intensity, setIntensity] = useState<number>(0);
  const [loading, setLoading] = useState<boolean>(true);

  useEffect(() => {
    const getLightIntensity = async () => {
      const currentIntensity = await fetchLightIntensity();
      setIntensity(currentIntensity);
      setLoading(false);
    };

    getLightIntensity();
  }, []);

  const handleIntensityChange = async (event: React.ChangeEvent<HTMLInputElement>) => {
    const newIntensity = Number(event.target.value);
    setIntensity(newIntensity);
    await updateLightIntensity(newIntensity);
  };

  if (loading) {
    return <div>Loading...</div>;
  }

  return (
    <div>
      <h2>Light Intensity Control</h2>
      <input
        type="range"
        min="0"
        max="255"
        value={intensity}
        onChange={handleIntensityChange}
      />
      <p>Current Intensity: {intensity}</p>
    </div>
  );
};

export default LightControl;