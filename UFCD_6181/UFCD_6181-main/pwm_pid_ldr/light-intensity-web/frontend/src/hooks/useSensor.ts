import { useEffect, useState } from 'react';
import { fetchLightIntensity } from '../services/api';

const useSensor = () => {
  const [lightIntensity, setLightIntensity] = useState<number | null>(null);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    const getLightIntensity = async () => {
      try {
        const intensity = await fetchLightIntensity();
        setLightIntensity(intensity);
      } catch (err) {
        setError('Failed to fetch light intensity');
      }
    };

    getLightIntensity();
    const interval = setInterval(getLightIntensity, 5000); // Fetch every 5 seconds

    return () => clearInterval(interval); // Cleanup on unmount
  }, []);

  return { lightIntensity, error };
};

export default useSensor;