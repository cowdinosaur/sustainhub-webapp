# SustainHub - Smart Fridge Manager

A mobile-optimized web application for tracking fridge ingredients, monitoring expiry dates, and getting meal recipe suggestions based on available ingredients.

## Features

- **Inventory Management**: View all ingredients in your fridge with quantities and expiry dates
- **Expiry Tracking**: See how many days until ingredients expire
- **Smart Recipe Suggestions**: Get meal ideas based on ingredients you have with match percentages
- **Recipe Details**: View complete recipes with color-coded ingredients (green = have, red = need)
- **Receipt Scanning**: AI-powered receipt scanning using OpenRouter (Claude 3.5 Sonnet) to automatically extract and add groceries
- **ESP32 Integration**: Backend API for ESP32 microcontroller to update ingredient data
- **Mobile-Optimized**: Responsive design following the lofi UI prototype

## Tech Stack

### Backend
- Node.js + Express
- SQLite database
- RESTful API

### Frontend
- React (with Vite)
- React Router for navigation
- Axios for API calls
- CSS3 with mobile-first responsive design

## Project Structure

```
sustainhub_webapp/
├── backend/
│   ├── server.js          # Express server with API endpoints
│   ├── fridge.db          # SQLite database (auto-generated)
│   ├── package.json
│   └── .env
├── frontend/
│   ├── src/
│   │   ├── pages/
│   │   │   ├── Cover.jsx          # Landing page
│   │   │   ├── Inventory.jsx      # Ingredients list
│   │   │   ├── MealIdeas.jsx      # Recipe suggestions
│   │   │   └── RecipeDetail.jsx   # Recipe details
│   │   ├── App.jsx        # Main app with routing
│   │   └── main.jsx       # Entry point
│   ├── package.json
│   └── index.html
└── README.md
```

## Getting Started

### Prerequisites
- Node.js (v14 or higher)
- npm

### Installation

1. **Clone or navigate to the project directory**

2. **Install backend dependencies**
   ```bash
   cd backend
   npm install
   ```

3. **Install frontend dependencies**
   ```bash
   cd ../frontend
   npm install
   ```

4. **(Optional) Set up OpenRouter for AI Receipt Scanning**

   To enable AI-powered receipt scanning:

   a. Get an API key from [OpenRouter](https://openrouter.ai/keys)

   b. Create a `.env` file in the `frontend` directory:
   ```bash
   cd frontend
   cp .env.example .env
   ```

   c. Add your OpenRouter API key to `frontend/.env`:
   ```
   VITE_OPENROUTER_API_KEY=your_api_key_here
   ```

   Without an API key, the receipt scanner will work in demo mode with mock data.

### Running the Application

You need to run both the backend and frontend servers:

**Terminal 1 - Backend Server:**
```bash
cd backend
npm start
```
The backend will run on `http://localhost:3001`

**Terminal 2 - Frontend Server:**
```bash
cd frontend
npm run dev
```
The frontend will run on `http://localhost:5173` (or another port if 5173 is busy)

Open your browser and navigate to the frontend URL (typically `http://localhost:5173`)

### Testing with Sample Data

To quickly test the application with sample ingredient data:

```bash
cd backend
npm run seed
```

This will populate the database with sample ingredients (tomato, apple, grapes, carrot, etc.) matching the lofi UI prototype.

### Testing the API (ESP32 Integration)

To test the API endpoints that the ESP32 will use:

```bash
cd backend
npm run test-api
```

This will simulate ESP32 API calls (adding, updating, and deleting ingredients).

## API Endpoints

### For ESP32 Microcontroller

**Add/Update Ingredient**
```http
POST http://localhost:3001/api/ingredients
Content-Type: application/json

{
  "name": "tomato",
  "category": "vegetable",
  "quantity": 5,
  "unit": "pieces",
  "expiry_date": "2025-11-30"
}
```

**Update Specific Ingredient**
```http
PUT http://localhost:3001/api/ingredients/{id}
Content-Type: application/json

{
  "name": "tomato",
  "category": "vegetable",
  "quantity": 3,
  "unit": "pieces",
  "expiry_date": "2025-11-30"
}
```

**Delete Ingredient**
```http
DELETE http://localhost:3001/api/ingredients/{id}
```

### For Web App

**Get All Ingredients**
```http
GET http://localhost:3001/api/ingredients
```

**Get Recipe Suggestions** (based on available ingredients)
```http
GET http://localhost:3001/api/recipes/suggestions
```

**Get All Recipes**
```http
GET http://localhost:3001/api/recipes
```

**Get Recipe by ID**
```http
GET http://localhost:3001/api/recipes/{id}
```

**Health Check**
```http
GET http://localhost:3001/api/health
```

## ESP32 Integration Example

Here's a simple example of how your ESP32 can send ingredient data:

```cpp
#include <HTTPClient.h>
#include <ArduinoJson.h>

void updateIngredient() {
  HTTPClient http;
  http.begin("http://YOUR_SERVER_IP:3001/api/ingredients");
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<200> doc;
  doc["name"] = "tomato";
  doc["category"] = "vegetable";
  doc["quantity"] = 5;
  doc["unit"] = "pieces";
  doc["expiry_date"] = "2025-11-30";

  String jsonString;
  serializeJson(doc, jsonString);

  int httpResponseCode = http.POST(jsonString);

  if (httpResponseCode > 0) {
    Serial.println("Ingredient updated successfully");
  } else {
    Serial.println("Error updating ingredient");
  }

  http.end();
}
```

## Pre-loaded Recipes

The database comes pre-loaded with 4 recipes:
1. **Tomato Soup** - Warm and comforting soup
2. **Fruit Salad** - Fresh fruit mix
3. **Caramel Apples** - Sweet caramel-coated apples
4. **Spaghetti** - Classic pasta with tomato sauce

## Recipe Suggestion Algorithm

The app suggests recipes based on ingredient matching:
- Calculates the percentage of recipe ingredients you have
- Shows recipes where you have at least 50% of ingredients
- Displays match percentage badge
- Sorts by best match first

## Mobile Optimization

- Responsive design for all screen sizes
- Touch-friendly buttons and navigation
- Optimized font sizes for mobile devices
- Fixed navigation bar for easy access
- Pastel color scheme matching the lofi UI prototype

## Future Enhancements

- AI-powered recipe suggestions using OpenAI API
- Barcode scanning for adding ingredients
- Shopping list generation
- Nutrition information
- User accounts and cloud sync
- Push notifications for expiring ingredients

## Development

**Backend development mode:**
```bash
cd backend
npm run dev
```

**Frontend development mode:**
```bash
cd frontend
npm run dev
```

**Build frontend for production:**
```bash
cd frontend
npm run build
```

## Troubleshooting

**Port already in use:**
- Backend: Change the PORT in `backend/.env`
- Frontend: Vite will automatically suggest another port

**CORS errors:**
- Make sure the backend is running on port 3001
- Check that frontend is making requests to `http://localhost:3001`

**Database not found:**
- The SQLite database is created automatically on first run
- Located at `backend/fridge.db`

## License

This project is open source and available for educational purposes.
