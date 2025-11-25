// Simulates ESP32 API calls for testing
const axios = require('axios');

const API_BASE_URL = 'http://localhost:3001/api';

// Helper function to get expiry date
function getExpiryDate(daysFromNow) {
  const date = new Date();
  date.setDate(date.getDate() + daysFromNow);
  return date.toISOString().split('T')[0];
}

async function testESP32Integration() {
  console.log('Starting ESP32 API integration test...\n');

  try {
    // 1. Add a new ingredient
    console.log('1. Adding new ingredient (banana)...');
    const addResponse = await axios.post(`${API_BASE_URL}/ingredients`, {
      name: 'banana',
      category: 'fruit',
      quantity: 6,
      unit: 'pieces',
      expiry_date: getExpiryDate(5)
    });
    console.log('✓ Success:', addResponse.data);
    const ingredientId = addResponse.data.id;

    // 2. Get all ingredients
    console.log('\n2. Fetching all ingredients...');
    const getAllResponse = await axios.get(`${API_BASE_URL}/ingredients`);
    console.log('✓ Total ingredients:', getAllResponse.data.length);
    console.log('  Ingredients:', getAllResponse.data.map(i => i.name).join(', '));

    // 3. Update the ingredient
    console.log('\n3. Updating banana quantity to 4...');
    await axios.put(`${API_BASE_URL}/ingredients/${ingredientId}`, {
      name: 'banana',
      category: 'fruit',
      quantity: 4,
      unit: 'pieces',
      expiry_date: getExpiryDate(5)
    });
    console.log('✓ Update successful');

    // 4. Get recipe suggestions
    console.log('\n4. Getting recipe suggestions...');
    const suggestionsResponse = await axios.get(`${API_BASE_URL}/recipes/suggestions`);
    console.log('✓ Suggested recipes:', suggestionsResponse.data.length);
    suggestionsResponse.data.forEach(recipe => {
      console.log(`  - ${recipe.name} (${Math.round(recipe.matchPercentage)}% match)`);
    });

    // 5. Delete the ingredient
    console.log('\n5. Deleting banana...');
    await axios.delete(`${API_BASE_URL}/ingredients/${ingredientId}`);
    console.log('✓ Deletion successful');

    console.log('\n✓ All ESP32 API tests completed successfully!');

  } catch (error) {
    console.error('\n✗ Error:', error.response?.data || error.message);
    console.error('Make sure the backend server is running on http://localhost:3001');
  }
}

// Check if axios is available
if (typeof axios === 'undefined') {
  console.error('Error: axios is not installed. Run: npm install axios');
  process.exit(1);
}

// Run the test
testESP32Integration();
