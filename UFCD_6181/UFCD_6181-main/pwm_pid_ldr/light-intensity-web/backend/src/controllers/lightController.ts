import { Request, Response } from 'express';
import { getLightIntensity, setLightIntensity } from '../services/lightService';

export const fetchLightIntensity = async (req: Request, res: Response) => {
  try {
    const intensity = await getLightIntensity();
    res.status(200).json({ intensity });
  } catch (error) {
    res.status(500).json({ error: 'Failed to fetch light intensity' });
  }
};

export const updateLightIntensity = async (req: Request, res: Response) => {
  const { intensity } = req.body;
  try {
    await setLightIntensity(intensity);
    res.status(200).json({ message: 'Light intensity updated successfully' });
  } catch (error) {
    res.status(500).json({ error: 'Failed to update light intensity' });
  }
};