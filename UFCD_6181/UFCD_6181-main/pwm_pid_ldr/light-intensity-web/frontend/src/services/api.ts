import axios from 'axios';

const API_BASE_URL = 'http://localhost:5000/api'; // Adjust the base URL as needed

export const fetchLightIntensity = async () => {
  try {
    const response = await axios.get(`${API_BASE_URL}/light-intensity`);
    return response.data;
  } catch (error) {
    console.error('Error fetching light intensity:', error);
    throw error;
  }
};

export const updateLightIntensity = async (intensity: number) => {
  try {
    const response = await axios.put(`${API_BASE_URL}/light-intensity`, { intensity });
    return response.data;
  } catch (error) {
    console.error('Error updating light intensity:', error);
    throw error;
  }
};